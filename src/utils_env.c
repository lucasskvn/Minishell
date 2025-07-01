/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** utils_env
*/
#include "my.h"

void find_env(char **environ, int index)
{
    for (int j = index; environ[j] != NULL; j++)
        environ[j] = environ[j + 1];
}

int print_environment(mainstruct_t *mainstruct)
{
    int i = 0;

    while (mainstruct->env[i] != NULL) {
        write(1, mainstruct->env[i], my_strlen(mainstruct->env[i]));
        write(1, "\n", 1);
        i++;
    }
    return 0;
}

char *my_getenv(mainstruct_t *mainstruct, char *name)
{
    int i = 0;
    size_t name_len;

    if (name == NULL || mainstruct->env == NULL)
        return NULL;
    name_len = my_strlen(name);
    while (mainstruct->env[i] != NULL) {
        if (my_strncmp(mainstruct->env[i], name, name_len) == 0 &&
            mainstruct->env[i][name_len] == '=') {
            return &mainstruct->env[i][name_len + 1];
        }
        i++;
    }
    return NULL;
}

char *find_value(char *name)
{
    char *value = NULL;
    char *equals_pos;

    equals_pos = my_strchr(name, '=');
    if (equals_pos != NULL) {
        *equals_pos = '\0';
        value = equals_pos + 1;
    } else {
        value = strtok(NULL, " \n\t\r\v\0");
    }
    return value;
}
