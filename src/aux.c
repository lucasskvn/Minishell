/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** aux
*/
#include "my.h"

static void free_env_memory(mainstruct_t *mainstruct, size_t allocated)
{
    for (size_t j = 0; j < allocated; j++)
        free(mainstruct->env[j]);
    free(mainstruct->env);
    mainstruct->env = NULL;
}

static int copy_env_entries(mainstruct_t *mainstruct, size_t env_count)
{
    extern char **environ;

    for (size_t i = 0; i < env_count; i++) {
        mainstruct->env[i] = my_strdup(environ[i]);
        if (mainstruct->env[i] == NULL) {
            free_env_memory(mainstruct, i);
            return 0;
        }
    }
    return 1;
}

void init_env(mainstruct_t *mainstruct)
{
    extern char **environ;
    size_t env_count = 0;
    char cwd[PATH_MAX];

    while (environ[env_count] != NULL)
        env_count++;
    mainstruct->env = malloc((env_count + 1) * sizeof(char *));
    if (mainstruct->env == NULL)
        return;
    if (!copy_env_entries(mainstruct, env_count))
        return;
    mainstruct->env[env_count] = NULL;
    sync_environ_with_mainstruct(mainstruct);
    if (getcwd(cwd, PATH_MAX) != NULL)
        my_setenv(mainstruct, "PWD", cwd, 1);
}

mainstruct_t init_mainstruct(void)
{
    mainstruct_t mainstruct;

    mainstruct.status = 0;
    mainstruct.line = NULL;
    mainstruct.exit = 0;
    mainstruct.read = 0;
    mainstruct.env = NULL;
    mainstruct.redir = 0;
    init_env(&mainstruct);
    return mainstruct;
}

int segfault(mainstruct_t mainstruct)
{
    if (WTERMSIG(mainstruct.status) == SIGSEGV) {
        write(2, "Segmentation fault (core dumped)\n", 33);
        return 139;
    }
    return mainstruct.status;
}

void sync_environ_with_mainstruct(mainstruct_t *mainstruct)
{
    extern char **environ;

    environ = mainstruct->env;
}

void free_environment(mainstruct_t *mainstruct)
{
    if (!mainstruct || !mainstruct->env)
        return;
    for (int i = 0; mainstruct->env[i] != NULL; i++)
        free(mainstruct->env[i]);
    free(mainstruct->env);
    mainstruct->env = NULL;
}
