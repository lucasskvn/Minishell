/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** cd
*/
#include "my.h"

static int error_messages(char *path)
{
    struct stat st;

    if (access(path, F_OK) == -1) {
        write(2, path, my_strlen(path));
        write(2, ": No such file or directory.\n", 29);
        return 1;
    }
    if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode)) {
        write(2, path, my_strlen(path));
        write(2, ": Not a directory.\n", 19);
        return 1;
    }
    if (access(path, X_OK) == -1) {
        write(2, path, my_strlen(path));
        write(2, ": Permission denied.\n", 21);
        return 1;
    }
    return 0;
}

static int cd_to_path(mainstruct_t *mainstruct, char *path, char *current_pwd)
{
    char abs_path[PATH_MAX];

    if (error_messages(path) == 1)
        return 1;
    if (chdir(path) == -1) {
        write(2, path, my_strlen(path));
        write(2, ": No such file or directory.\n", 29);
        return 1;
    }
    if (getcwd(abs_path, PATH_MAX) == NULL)
        return 1;
    my_setenv(mainstruct, "OLDPWD", current_pwd, 1);
    my_setenv(mainstruct, "PWD", abs_path, 1);
    return 0;
}

int change_directory(mainstruct_t *mainstruct)
{
    char *token = strtok(mainstruct->line, " \n\t\r\v\0");
    char *p = strtok(NULL, " \n\t\r\v\0");
    char *extra_arg = strtok(NULL, " \n\t\r\v\0");
    char *current_pwd = my_getenv(mainstruct, "PWD");
    char *oldpwd = my_getenv(mainstruct, "OLDPWD");

    if (token == NULL)
        return 1;
    if (extra_arg != NULL) {
        write(2, "cd: Too many arguments.\n", 24);
        return 1;
    }
    if (oldpwd == NULL)
        my_setenv(mainstruct, "OLDPWD", current_pwd, 1);
    if (p == NULL || my_strcmp(p, "~") == 0 || my_strcmp(p, "$HOME") == 0)
        return cdtohome(mainstruct, current_pwd);
    else if (my_strcmp(p, "-") == 0)
        return cdtoprev(mainstruct, current_pwd);
    else
        return cd_to_path(mainstruct, p, current_pwd);
}
