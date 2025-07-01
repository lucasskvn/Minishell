/*
** EPITECH PROJECT, 2024
** my_strcapitalize
** File description:
** capitalize the first letter of a word
*/
#include "my.h"

static char *lowcasent(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
        i = i + 1;
    }
    return str;
}

static void ifent2(char *str, int i)
{
    if (i == 0 || str[i - 1] == ' ' ||
            str[i - 1] == '+' || str[i - 1] == '-') {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
}

char *my_strcapitalize(char *str)
{
    int i = 0;

    str = lowcasent(str);
    while (str[i] != '\0') {
        ifent2(str, i);
        i = i + 1;
    }
    return str;
}
