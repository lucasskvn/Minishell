/*
** EPITECH PROJECT, 2024
** my_find_prime_sup
** File description:
** return the smallest prime nbr that is greater or equal to nbr given
*/
#include "my.h"

static int find_prime(int nb)
{
    if (nb == 0)
        return 0;
    else if (nb == 2 || nb == 3)
        return 1;
    if (nb % 3 == 0)
        return 0;
    else
        return 1;
}

int my_find_prime_sup(int nb)
{
    if (nb > 2 && nb % 2 == 0)
        nb = nb + 1;
    while (find_prime(nb) == 0)
        nb = nb + 2;
    return nb;
}
