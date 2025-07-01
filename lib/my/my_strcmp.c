/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** check if s1 is greater than, less than, or equal to s2
*/
#include "my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i = i + 1;
    }
    return s1[i] - s2[i];
}
