/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-lucas.sangkhavongs
** File description:
** clean_str
*/
#include "my.h"

char *removetabs(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '\t')
            str[i] = ' ';
        i = i + 1;
    }
    return str;
}

int writestr(char *tmp)
{
    int j = 0;

    while (tmp[j] != '\0') {
        if (tmp[j] == ' ' && tmp[j + 1] == '\0')
            return 0;
        write(1, &tmp[j], 1);
        j = j + 1;
    }
    return 0;
}

int removespaces(char *str, int i)
{
    if (str[i] == ' ' && (i == 0 || (i > 0 && str[i - 1] == ' ')
        || str[i + 1] == '\0')) {
        while (str[i] == ' ')
            i = i + 1;
    }
    return i;
}

char *clean_str(char *str)
{
    int i = 0;
    int j = 0;
    char tmp[256];
    char *cleaned_str;

    str = removetabs(str);
    while (str[i] != '\0') {
        i = removespaces(str, i);
        if (str[i] != '\0') {
            tmp[j] = str[i];
            j = j + 1;
            i = i + 1;
        }
    }
    tmp[j] = '\0';
    cleaned_str = my_strdup(tmp);
    return cleaned_str;
}

char *init_cleanstr(mainstruct_t mainstruct)
{
    char *cleaned_str;

    if (mainstruct.line[mainstruct.read - 1] == '\n')
        mainstruct.line[mainstruct.read - 1] = '\0';
    cleaned_str = clean_str(mainstruct.line);
    return cleaned_str;
}
