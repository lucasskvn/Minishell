/*
** EPITECH PROJECT, 2024
** my_strstr
** File description:
** compare two strings
*/
#include "my.h"

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int j;
    char *str_tmp;
    char const *find_tmp;

    if (*to_find == '\0')
        return str;
    while (str[i] != '\0') {
        j = 0;
        str_tmp = &str[i];
        find_tmp = to_find;
        while (str_tmp[j] != '\0' && find_tmp[j] != '\0'
                && str_tmp[j] == find_tmp[j]) {
            j++;
        }
        if (find_tmp[j] == '\0')
            return &str[i];
        i = i + 1;
    }
    return 0;
}
