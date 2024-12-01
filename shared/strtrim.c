/*
** EPITECH PROJECT, 2024
** myftp [WSL: Ubuntu]
** File description:
** strtrim
*/

#include "../include/shared.h"

char *strtrim(char *str)
{
    char *end;

    while (isspace((unsigned char)*str)) {
        str++;
    }
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    end[1] = '\0';
    return str;
}
