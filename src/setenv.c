/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** aux2
*/
#include "my.h"

static char *create_env_entry(char *name, char *value, int name_len)
{
    char *new_env = malloc(name_len + my_strlen(value) + 2);

    if (new_env == NULL)
        return NULL;
    my_strcpy(new_env, name);
    my_strcat(new_env, "=");
    my_strcat(new_env, value);
    return new_env;
}

static int update_existing_env(mainstruct_t *mainstruct, char *name,
    char *value, int overwrite)
{
    int name_len = my_strlen(name);
    char *new_env;

    for (int i = 0; mainstruct->env[i] != NULL;) {
        if (my_strncmp(mainstruct->env[i], name, name_len) != 0 ||
            mainstruct->env[i][name_len] != '=') {
            i++;
            continue;
        }
        if (!overwrite)
            return 0;
        free(mainstruct->env[i]);
        new_env = create_env_entry(name, value, name_len);
        if (new_env == NULL)
            return 1;
        mainstruct->env[i] = new_env;
        sync_environ_with_mainstruct(mainstruct);
        return 0;
    }
    return -1;
}

static char **allocate_new_env_array(int env_size)
{
    char **new_env_array = malloc((env_size + 2) * sizeof(char *));

    return new_env_array;
}

static int finish_add_env(mainstruct_t *mainstruct, char **new_env_array)
{
    free(mainstruct->env);
    mainstruct->env = new_env_array;
    sync_environ_with_mainstruct(mainstruct);
    return 0;
}

static int copy_and_add_env(mainstruct_t *mainstruct, char *name,
    char *value, int name_len)
{
    int env_size = 0;
    char *new_env;
    char **new_env_array;

    while (mainstruct->env[env_size] != NULL)
        env_size++;
    new_env_array = allocate_new_env_array(env_size);
    if (new_env_array == NULL)
        return 1;
    for (int i = 0; i < env_size; i++)
        new_env_array[i] = mainstruct->env[i];
    new_env = create_env_entry(name, value, name_len);
    if (new_env == NULL) {
        free(new_env_array);
        return 1;
    }
    new_env_array[env_size] = new_env;
    new_env_array[env_size + 1] = NULL;
    return finish_add_env(mainstruct, new_env_array);
}

int my_setenv(mainstruct_t *mainstruct, char *name,
    char *value, int overwrite)
{
    int name_len;

    if (name == NULL || name[0] == '\0' || my_strchr(name, '=') != NULL)
        return 1;
    name_len = my_strlen(name);
    if (update_existing_env(mainstruct, name, value, overwrite) == 0)
        return 0;
    return copy_and_add_env(mainstruct, name, value, name_len);
}
