/*
** EPITECH PROJECT, 2024
** my_str_isupper
** File description:
** check if all str is uppercase
*/
#include "my.h"

int my_str_isupper(char const *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (str[i] < 'A' || str[i] > 'Z') {
            return 0;
        }
        i = i + 1;
    }
    return 1;
}
