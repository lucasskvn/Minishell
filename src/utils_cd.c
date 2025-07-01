/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** utils_cd
*/
#include "my.h"

int cdtohome(mainstruct_t *mainstruct, char *current_pwd)
{
    char abs_path[PATH_MAX];

    my_setenv(mainstruct, "OLDPWD", current_pwd, 1);
    chdir(my_getenv(mainstruct, "HOME"));
    if (getcwd(abs_path, PATH_MAX) != NULL) {
        my_setenv(mainstruct, "PWD", abs_path, 1);
    } else {
        my_setenv(mainstruct, "PWD", my_getenv(mainstruct, "HOME"), 1);
    }
    return 0;
}

int updatepwd(mainstruct_t *mainstruct,
    char abs_path[PATH_MAX], char *oldpwd)
{
    if (getcwd(abs_path, PATH_MAX) != NULL) {
        my_setenv(mainstruct, "PWD", abs_path, 1);
        write(1, abs_path, my_strlen(abs_path));
        write(1, "\n", 1);
    } else {
        my_setenv(mainstruct, "PWD", oldpwd, 1);
        write(1, oldpwd, my_strlen(oldpwd));
        write(1, "\n", 1);
    }
    return 0;
}

int cdtoprev(mainstruct_t *mainstruct, char *current_pwd)
{
    char abs_path[PATH_MAX];
    char *oldpwd = my_getenv(mainstruct, "OLDPWD");

    if (oldpwd == NULL || oldpwd[0] == '\0') {
        write(1, ": No such file or directory.\n", 29);
        return 1;
    }
    chdir(oldpwd);
    my_setenv(mainstruct, "OLDPWD", current_pwd, 1);
    return updatepwd(mainstruct, abs_path, oldpwd);
}
