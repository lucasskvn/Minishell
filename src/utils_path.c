/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** utils_path
*/
#include "my.h"

static int count_paths(char *path_copy)
{
    char *token;
    int count = 0;

    token = strtok(path_copy, ":");
    while (token != NULL) {
        count++;
        token = strtok(NULL, ":");
    }
    return count;
}

static char **allocate_directories(char *path, int count)
{
    char **directories = malloc((count + 1) * sizeof(char *));
    char *path_copy;
    char *token;
    int i = 0;

    path_copy = my_strdup(path);
    if (!path_copy) {
        free(directories);
        return NULL;
    }
    token = strtok(path_copy, ":");
    while (token != NULL) {
        directories[i] = my_strdup(token);
        i++;
        token = strtok(NULL, ":");
    }
    directories[i] = NULL;
    free(path_copy);
    return directories;
}

char **get_path_directories(mainstruct_t *mainstruct)
{
    char *path = my_getenv(mainstruct, "PATH");
    char *path_copy;
    int count;

    if (!path)
        return NULL;
    path_copy = my_strdup(path);
    if (!path_copy)
        return NULL;
    count = count_paths(path_copy);
    free(path_copy);
    return allocate_directories(path, count);
}
