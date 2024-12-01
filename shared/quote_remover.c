/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** quote_remover
*/

#include "../include/shared.h"

char *removequotes(const char *arg)
{
    size_t len;
    char *result;
    char *p;

    if (arg == NULL)
        return NULL;
    len = strlen(arg);
    result = malloc(len + 1);
    p = result;
    for (const char *q = arg; *q; q++) {
        if (*q != '\"') {
            *p = *q;
            p++;
        }
    }
    *p = '\0';
    return result;
}

char **removequotesfromargs(char **args)
{
    char **result;
    int count = 0;

    while (args[count])
        count++;
    result = malloc(sizeof(char *) * (count + 1));
    for (int i = 0; i < count; i++)
        result[i] = removequotes(args[i]);
    result[count] = NULL;
    return result;
}

void freestringarray(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);
}

char *addquotes(const char *arg)
{
    size_t len;
    char *result;
    char *p;
    const char *q;

    if (arg == NULL)
        return NULL;
    len = strlen(arg);
    result = malloc(len + 3);
    p = result;
    *p = '\"';
    p++;
    for (q = arg; *q; q++) {
        *p = *q;
        p++;
    }
    *p = '\"';
    p++;
    *p = '\0';
    return result;
}
