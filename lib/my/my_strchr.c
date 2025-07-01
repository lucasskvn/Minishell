/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** my_strchr
*/
#include "my.h"

char *my_strchr(const char *str, int c)
{
    if (str == NULL)
        return NULL;
    while (*str != '\0') {
        if (*str == (char)c)
            return (char *)str;
        str++;
    }
    if ((char)c == '\0')
        return (char *)str;
    return NULL;
}
