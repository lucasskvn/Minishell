/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** path
*/
#include "my.h"

static char *check_direct_path(char *command)
{
    struct stat st;

    if (my_strchr(command, '/')) {
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
            return my_strdup(command);
        return NULL;
    }
    return NULL;
}

static char *build_command_path(char *path, char *command)
{
    char *full_path = malloc(my_strlen(path) + my_strlen(command) + 2);

    if (!full_path)
        return NULL;
    my_strcpy(full_path, path);
    my_strcat(full_path, "/");
    my_strcat(full_path, command);
    return full_path;
}

static char *try_paths(char **paths, char *command)
{
    struct stat st;
    char *full_path = NULL;

    for (int i = 0; paths[i] != NULL; i++) {
        full_path = build_command_path(paths[i], command);
        if (!full_path)
            continue;
        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
            return full_path;
        free(full_path);
    }
    return NULL;
}

static void free_paths(char **paths)
{
    for (int i = 0; paths[i] != NULL; i++)
        free(paths[i]);
    free(paths);
}

char *find_command_path(mainstruct_t *mainstruct, char *command)
{
    char **paths = get_path_directories(mainstruct);
    char *direct_path = check_direct_path(command);
    char *found_path = NULL;

    if (direct_path)
        return direct_path;
    if (!paths)
        return NULL;
    found_path = try_paths(paths, command);
    if (found_path) {
        free_paths(paths);
        return found_path;
    }
    free_paths(paths);
    return NULL;
}
