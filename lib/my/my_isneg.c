/*
** EPITECH PROJECT, 2024
** my_isneg
** File description:
** check if a number is negative
*/
#include "my.h"

int my_isneg(int n)
{
    char neg;
    char nneg;

    neg = 'N';
    nneg = 'P';
    if (n < 0) {
        my_putchar(neg);
    } else {
        my_putchar(nneg);
    }
}
