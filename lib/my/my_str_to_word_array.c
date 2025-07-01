/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** split string into words
*/
#include "my.h"

static int alphan(char c)
{
    return (c >= 'a' && c <= 'z') ||
    (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

static int word_count(char *str)
{
    int count = 0;
    int iw = 0;
    int i = 0;
    int len = my_strlen(str);

    while (i < len) {
        if (alphan(str[i]) && iw != 1) {
                iw = 1;
                count = count + 1;
        }
        if (alphan(str[i]) != 1) {
            iw = 0;
        }
        i = i + 1;
    }
    return count - 1;
}

static char *extract_word(char const *str, int *index)
{
    int len = 0;
    int start = *index;
    char *word;

    while (str[*index] != '\0' && alphan(str[*index])) {
        len++;
        (*index)++;
    }
    word = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++) {
        word[i] = str[start + i];
    }
    word[len] = '\0';
    return word;
}

char **my_str_to_word_array(char const *str)
{
    int num_words = word_count((char *)str);
    char **array = malloc(sizeof(char *) * (num_words + 1));
    int j = 0;

    for (int i = 0; str[i] != '\0';) {
        if (alphan(str[i])) {
            array[j] = extract_word(str, &i);
            j++;
        } else {
            i++;
        }
    }
    array[j] = NULL;
    return array;
}
