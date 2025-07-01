/*
** EPITECH PROJECT, 2024
** my_show_word_array
** File description:
** display content of a array of words
*/
#include "my.h"

int my_show_word_array(char *const *tab)
{
    int i = 0;

    while (tab[i] != 0) {
        my_putstr(tab[i]);
        write(1, "\n", 1);
        i = i + 1;
    }
    return 0;
}
