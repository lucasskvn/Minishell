/*
** EPITECH PROJECT, 2024
** my_swap
** File description:
** swap the content of two ints
*/
#include "my.h"

void my_swap(int *a, int *b)
{
    int c = *a;

    *a = *b;
    *b = c;
}
