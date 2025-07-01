/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** commands
*/
#include "my.h"

static int count_words(const char *str)
{
    int count = 0;
    bool in_word = false;

    for (int i = 0; str[i]; i++) {
        if (!isspace(str[i]) && !in_word) {
            in_word = true;
            count++;
        }
        if (isspace(str[i]) && in_word)
            in_word = false;
    }
    return count;
}

static char *build_full_path(char *token)
{
    char *path = malloc(my_strlen(token) + 6);

    if (!path)
        return NULL;
    my_strcpy(path, "/bin/");
    my_strcat(path, token);
    return path;
}

static char *get_first_argument(char *token)
{
    char *path = NULL;

    if (token[0] == '.' && token[1] == '/')
        return my_strdup(token);
    if (token[0] != '/' && token[0] != '.' && token[0] != '\0') {
        path = build_full_path(token);
        return path ? path : my_strdup(token);
    }
    return my_strdup(token);
}

void free_arguments(char **argv)
{
    if (!argv)
        return;
    for (int i = 0; argv[i] != NULL; i++)
        free(argv[i]);
    free(argv);
}

static void fill_arguments(char *token, char **argv, char *line_copy)
{
    int argc = 1;

    while (token != NULL) {
        argv[argc] = my_strdup(token);
        if (!argv[argc]) {
            free_arguments(argv);
            argv[0] = NULL;
            free(line_copy);
            return;
        }
        argc++;
        token = strtok(NULL, " \n\t\r\v\0");
    }
    argv[argc] = NULL;
    free(line_copy);
}

void parse_arguments(char *line, char **argv)
{
    char *line_copy = my_strdup(line);
    char *token;

    if (!line_copy)
        return;
    token = strtok(line_copy, " \n\t\r\v\0");
    if (!token) {
        free(line_copy);
        return;
    }
    argv[0] = get_first_argument(token);
    token = strtok(NULL, " \n\t\r\v\0");
    if (!token) {
        argv[1] = NULL;
        free(line_copy);
        return;
    }
    fill_arguments(token, argv, line_copy);
}

mainstruct_t execute_other(mainstruct_t mainstruct)
{
    int argc_max = count_words(mainstruct.line) + 1;
    char **argv = malloc(sizeof(char *) * argc_max);

    if (!argv)
        return mainstruct;
    parse_arguments(mainstruct.line, argv);
    if (argv[0])
        mainstruct.status = exec(argv, &mainstruct);
    free_arguments(argv);
    return mainstruct;
}
