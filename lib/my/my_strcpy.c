/*
** EPITECH PROJECT, 2024
** my_strcpy
** File description:
** copy string into an other
*/
#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i = i + 1;
    }
    dest[i] = '\0';
    return dest;
}
