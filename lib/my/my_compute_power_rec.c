/*
** EPITECH PROJECT, 2024
** my_compute_power_rec
** File description:
** recursive function
*/
#include "my.h"

int my_compute_power_rec(int nb, int p)
{
    if (p < 0)
        return 0;
    if (p == 0)
        return 1;
    return nb * my_compute_power_rec(nb, p - 1);
}
