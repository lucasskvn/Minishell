/*
** EPITECH PROJECT, 2024
** my_str_isnum
** File description:
** check if all str is num
*/
#include "my.h"

int my_str_isnum(char const *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
        i = i + 1;
    }
    return 1;
}
