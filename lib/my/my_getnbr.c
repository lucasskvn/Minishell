/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** return a number in a string
*/
#include "my.h"

int my_getnbr(char const *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\n') {
        i = i + 1;
    }
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -1;
        i = i + 1;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i = i + 1;
    }
    return result * sign;
}
