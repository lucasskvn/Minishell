/*
** EPITECH PROJECT, 2024
** my_sort_int_array
** File description:
** sort int in a array
*/
#include "my.h"

static int infent(int *tab, int j, int min_idx)
{
    if (tab[j] < tab[min_idx]) {
        min_idx = j;
    }
    return min_idx;
}

void my_sort_int_array(int *tab, int size)
{
    int min_idx;
    int temp;

    for (int i = 0; i < size - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < size; j++) {
            min_idx = infent(tab, j, min_idx);
        }
        temp = tab[min_idx];
        tab[min_idx] = tab[i];
        tab[i] = temp;
    }
}
