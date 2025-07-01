/*
** EPITECH PROJECT, 2024
** my_revstr
** File description:
** function that reverse str
*/
#include "my.h"

char *my_revstr(char *str)
{
    int len = my_strlen(str);
    int i = 0;
    int j = len - 1;
    char temp;

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i = i + 1;
        j = j - 1;
    }
    return str;
}
