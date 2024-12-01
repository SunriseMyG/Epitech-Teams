/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** quote_parser
*/

#include "../include/shared.h"

char *mergequotes(char **args, int *index, bool keep_quotes)
{
    size_t initial_len = strlen(args[*index]);
    char *merged = malloc(initial_len + 1);
    size_t arg_len;

    strcpy(merged, keep_quotes ? args[*index] : args[*index] + 1);
    for (int has_end_quote = 0; args[++(*index)];) {
        arg_len = strlen(args[*index]);
        has_end_quote = args[*index][arg_len - 1] == '\"';
        if (has_end_quote && !keep_quotes)
            arg_len--;
        merged = realloc(merged, strlen(merged) + arg_len + 2);
        strcat(merged, " ");
        strncat(merged, args[*index], arg_len);
        if (has_end_quote)
            break;
    }
    return merged;
}

char **quote_parser(char **args, bool keep_quotes)
{
    char **parsed = malloc(sizeof(char *) * 256);
    int i = 0;
    int j = 0;

    while (args[i]) {
        if (args[i][0] == '\"' && args[i][strlen(args[i]) - 1] != '\"') {
            parsed[j] = mergequotes(args, &i, keep_quotes);
            j++;
        } else {
            parsed[j] = strdup(args[i]);
            j++;
        }
        i++;
    }
    parsed[j] = NULL;
    return parsed;
}

void free_parsed_args(char **parsed)
{
    for (int i = 0; parsed[i] != NULL; i++)
        free(parsed[i]);
    free(parsed);
}
