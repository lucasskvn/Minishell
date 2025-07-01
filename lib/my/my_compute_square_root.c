/*
** EPITECH PROJECT, 2024
** my_compute_square_root
** File description:
** make square root
*/
#include "my.h"

int my_compute_square_root(int nb)
{
    int res = 1;

    if (nb <= 0)
        return 0;
    while (res * res <= nb) {
        if (res * res == nb)
            return res;
        res++;
    }
    return 0;
}
