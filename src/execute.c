/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** execute
*/
#include "my.h"

static int update_pwd(mainstruct_t *mainstruct, char *abs_path)
{
    char *current_pwd = my_getenv(mainstruct, "PWD");

    if (!getcwd(abs_path, PATH_MAX))
        return 1;
    my_setenv(mainstruct, "OLDPWD", current_pwd, 1);
    my_setenv(mainstruct, "PWD", abs_path, 1);
    return 0;
}

static int handle_directory(char **argv, mainstruct_t *mainstruct)
{
    struct stat st;
    char abs_path[PATH_MAX];

    if (stat(argv[0], &st) != 0 || !S_ISDIR(st.st_mode))
        return -1;
    if (chdir(argv[0]) == -1) {
        write(2, argv[0], my_strlen(argv[0]));
        write(2, ": Permission denied.\n", 21);
        return 1;
    }
    return update_pwd(mainstruct, abs_path);
}

static void prepare_command(char **argv, mainstruct_t *mainstruct, char **orig)
{
    if (!my_strncmp(mainstruct->line, "./", 2)) {
        *orig = argv[0];
        argv[0] = my_strdup(mainstruct->line + 2);
    }
}

static void restore_original(char **argv, char *orig)
{
    if (orig) {
        free(argv[0]);
        argv[0] = orig;
    }
}

static int is_error_status(mainstruct_t *mainstruct)
{
    return WIFEXITED(mainstruct->status)
        && WEXITSTATUS(mainstruct->status) != 0;
}

static int execute_command(char **argv, mainstruct_t *mainstruct)
{
    pid_t pid = fork();

    if (pid == 0) {
        execve(argv[0], argv, mainstruct->env);
        // remove /bin/bash argv[0]
        if (my_strncmp(argv[0], "/bin/bash", 9) == 0) {
            char *new_argv[3] = {"/bin/bash", "-c", argv[0]};
            execve("/bin/bash", new_argv, mainstruct->env);
        }
        write(2, argv[0], my_strlen(argv[0]));
        write(2, ": Command not found.\n", 22);
        exit(1);
    }
    mainstruct->status = execerror(mainstruct);
    return mainstruct->status;
}

int exec(char **argv, mainstruct_t *mainstruct)
{
    char *orig = NULL;
    int res;

    prepare_command(argv, mainstruct, &orig);
    res = handle_directory(argv, mainstruct);
    if (res != -1) {
        restore_original(argv, orig);
        return res;
    }
    res = execute_command(argv, mainstruct);
    restore_original(argv, orig);
    return res;
}

int execerror(mainstruct_t *mainstruct)
{
    wait(&mainstruct->status);
    if (is_error_status(mainstruct))
        return WEXITSTATUS(mainstruct->status);
    if (WIFSIGNALED(mainstruct->status))
        mainstruct->status = segfault(*mainstruct);
    return mainstruct->status;
}
