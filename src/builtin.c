/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** builtin
*/
#include "my.h"

int is_builtin_command(char *cmd)
{
    if (!cmd)
        return 0;
    return (my_strcmp(cmd, "cd") == 0 ||
            my_strcmp(cmd, "exit") == 0 ||
            my_strcmp(cmd, "env") == 0 ||
            my_strncmp(cmd, "setenv", 6) == 0 ||
            my_strncmp(cmd, "unsetenv", 8) == 0);
}

static int handle_exit(char **argv, mainstruct_t *mainstruct)
{
    if (my_strcmp(argv[0], "exit") == 0) {
        mainstruct->exit = 1;
        return 0;
    }
    return -1;
}

static int handle_simple_builtins(char **argv, mainstruct_t *mainstruct)
{
    if (my_strcmp(argv[0], "cd") == 0)
        return change_directory(mainstruct);
    if (my_strcmp(argv[0], "env") == 0)
        return print_environment(mainstruct);
    return -1;
}

static void build_cmd_line(char **argv, char *cmd_line)
{
    for (int i = 0; argv[i]; i++) {
        if (i > 0)
            my_strcat(cmd_line, " ");
        my_strcat(cmd_line, argv[i]);
    }
}

static int handle_env_builtins(char **argv, mainstruct_t *mainstruct)
{
    char *cmd_line = malloc(sizeof(char) * my_strlen(argv[0]) + 1);
    int result = -1;

    if (!cmd_line)
        return -1;
    cmd_line[0] = '\0';
    if (my_strncmp(argv[0], "setenv", 6) == 0) {
        build_cmd_line(argv, cmd_line);
        result = set_environment(mainstruct, cmd_line);
    } else if (my_strncmp(argv[0], "unsetenv", 8) == 0) {
        build_cmd_line(argv, cmd_line);
        result = unset_environment(mainstruct, cmd_line);
    }
    free(cmd_line);
    return result;
}

int execute_builtin(char **argv, mainstruct_t *mainstruct)
{
    int status = 0;

    if (handle_exit(argv, mainstruct) != -1) {
        status = handle_exit(argv, mainstruct);
        return status;
    }
    if (handle_simple_builtins(argv, mainstruct) != -1) {
        status = handle_simple_builtins(argv, mainstruct);
        return status;
    }
    if (handle_env_builtins(argv, mainstruct) != -1) {
        status = handle_env_builtins(argv, mainstruct);
        return status;
    }
    return 1;
}
