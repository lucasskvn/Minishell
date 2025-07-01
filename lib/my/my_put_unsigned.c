/*
** EPITECH PROJECT, 2024
** mprtf
** File description:
** my_put_unsigned
*/
#include "my.h"

int my_put_unsigned(unsigned int n)
{
    if (n >= 10)
        my_put_nbr(n / 10);
    my_putchar((n % 10) + '0');
    return 0;
}
