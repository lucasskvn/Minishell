/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** dupplicate str
*/
#include "my.h"

char *my_strdup(char const *src)
{
    char *dup;
    int i = 0;
    int lim = 0;

    lim = my_strlen(src);
    dup = malloc(sizeof(char) * (lim + 1));
    while (i < lim) {
        dup[i] = src[i];
        i = i + 1;
    }
    dup[i] = '\0';
    return dup;
}
