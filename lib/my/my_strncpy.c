/*
** EPITECH PROJECT, 2024
** my_strncpy
** File description:
** copy n chr from a string into another
*/
#include "my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;
    int len = 0;

    while (src[len] != '\0') {
        len = len + 1;
    }
    if (len < n)
        dest[len] = '\0';
    while (i != n) {
        dest[i] = src[i];
        i = i + 1;
    }
    return dest;
}
