/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** return len of str
*/
#include "my.h"

int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != '\0') {
        len = len + 1;
    }
    return len;
}
