/*
** EPITECH PROJECT, 2024
** my_str_isalpha
** File description:
** check if all str is alpha
*/
#include "my.h"

int my_str_isalpha(char const *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
        (str[i] >= 'a' && str[i] <= 'z'))) {
            return 0;
        }
        i = i + 1;
    }
    return 1;
}
