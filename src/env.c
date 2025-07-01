/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** env
*/
#include "my.h"

int unset_environment(mainstruct_t *mainstruct, char *line)
{
    char *token = strtok(line, " \n\t\r\v\0");
    char *name = strtok(NULL, " \n\t\r\v\0");

    if (token == NULL)
        return 1;
    if (name == NULL) {
        write(1, "unsetenv: Too few arguments.\n", 29);
        return 1;
    }
    for (int i = 0; mainstruct->env[i] != NULL; i++) {
        if (my_strncmp(mainstruct->env[i], name, my_strlen(name)) == 0 &&
            mainstruct->env[i][my_strlen(name)] == '=') {
            free(mainstruct->env[i]);
            find_env(mainstruct->env, i);
            sync_environ_with_mainstruct(mainstruct);
            break;
        }
    }
    return 0;
}

int modifenviron(mainstruct_t *mainstruct, int i, char *name, char *value)
{
    char *newenv;

    mainstruct->env[i] = malloc(my_strlen(name) + my_strlen(value) + 2);
    if (mainstruct->env[i] == NULL)
        return -1;
    newenv = malloc(my_strlen(name) + my_strlen(value) + 2);
    if (newenv == NULL) {
        free(mainstruct->env[i]);
        return -1;
    }
    newenv[0] = '\0';
    my_strcat(newenv, name);
    my_strcat(newenv, "=");
    my_strcat(newenv, value);
    my_strcpy(mainstruct->env[i], newenv);
    free(newenv);
    mainstruct->env[i + 1] = NULL;
    return 0;
}

int addenv(mainstruct_t *mainstruct, char *name, char *value)
{
    int i;
    size_t len = my_strlen(name);
    char *newenv = malloc(len + my_strlen(value) + 2);

    for (i = 0; mainstruct->env[i] != NULL; i++) {
        if (my_strncmp(mainstruct->env[i], name, len) == 0 &&
            mainstruct->env[i][len] == '=') {
            free(mainstruct->env[i]);
            mainstruct->env[i] = malloc(len + my_strlen(value) + 2);
            my_strcpy(newenv, name);
            my_strcat(newenv, "=");
            my_strcat(newenv, value);
            my_strcpy(mainstruct->env[i], newenv);
            return 0;
        }
    }
    modifenviron(mainstruct, i, name, value);
    return 0;
}

int is_valid_env_name(char *name)
{
    if (name == NULL || name[0] == '\0')
        return 0;
    if (!isalpha(name[0]) && name[0] != '_')
        return 0;
    for (int i = 1; name[i] != '\0'; i++) {
        if (!isalnum(name[i]) && name[i] != '_')
            return 0;
    }
    return 1;
}

static int print_error(char *name)
{
    if (!is_valid_env_name(name)) {
        write(1, "setenv: Variable name must", 26);
        write(1, " contain alphanumeric characters.\n", 35);
        return 1;
    }
    return 0;
}

int set_environment(mainstruct_t *mainstruct, char *line)
{
    char *token = strtok(line, " \n\t\r\v\0");
    char *name = NULL;
    char *value = NULL;

    if (token == NULL)
        return 1;
    if (my_strcmp(token, "setenv") == 0) {
        name = strtok(NULL, " \n\t\r\v\0");
        if (name == NULL)
            return print_environment(mainstruct);
    } else
        name = token;
    value = find_value(name);
    if (print_error(name) == 1)
        return 1;
    if (value == NULL)
        value = "";
    return addenv(mainstruct, name, value);
}
