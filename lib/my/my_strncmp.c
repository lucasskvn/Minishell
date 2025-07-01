/*
** EPITECH PROJECT, 2024
** my_strncmp
** File description:
** check if s1 is greater than, less than, or equal to s2 with n characters
*/
#include "my.h"

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (i < n && s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i = i + 1;
    }
    if (i < n) {
        if (s1[i] != '\0')
            return s1[i];
        if (s2[i] != '\0')
            return - s2[i];
    }
    return 0;
}
