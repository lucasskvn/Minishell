/*
** EPITECH PROJECT, 2024
** concat_params
** File description:
** put args in one string
*/
#include <stdlib.h>
#include <unistd.h>

static int arglen(int argc, char **argv)
{
    int i = 0;
    int j = 0;
    int len = 0;

    while (j < argc) {
        i = 0;
        while (argv[j][i] != '\0') {
            i = i + 1;
            len = len + 1;
        }
        j = j + 1;
    }
    return len;
}

char *concat_params(int argc, char **argv)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char *str;

    str = malloc(sizeof(char) * arglen(argc, argv));
    while (j < argc) {
        i = 0;
        while (argv[j][i] != '\0') {
            str[k] = argv[j][i];
            k = k + 1;
            i = i + 1;
        }
        str[k] = '\n';
        k = k + 1;
        j = j + 1;
    }
    str[k] = '\0';
    return str;
}
