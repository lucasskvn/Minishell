/*
** EPITECH PROJECT, 2024
** my_is_prime
** File description:
** find if a number is prime
*/
#include "my.h"

int my_is_prime(int nb)
{
    if (nb <= 1)
        return 0;
    if (nb == 2 || nb == 3)
        return 1;
    if (nb % 2 == 0 || nb % 3 == 0)
        return 0;
    for (int i = 5; i * i <= nb; i += 6) {
        if (nb % i == 0 || nb % (i + 2) == 0)
            return 0;
    }
    return 1;
}
