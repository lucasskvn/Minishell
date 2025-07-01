/*
** EPITECH PROJECT, 2024
** my_str_islower
** File description:
** check if all str is lowercase
*/
#include "my.h"

int my_str_isprintable(char const *str)
{
    int i = 0;
    int boolent = 0;

    if (str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (str[i] == 127 || str[i] < 21) {
            boolent = 1;
        }
        i = i + 1;
    }
    if (boolent == 0)
        return 1;
    else
        return 0;
}
