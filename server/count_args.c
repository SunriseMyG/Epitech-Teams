/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine [WSL : Ubuntu]
** File description:
** count_args
*/

#include "../include/server.h"

int count_args(char **args)
{
    int count = 0;

    while (args[count] != NULL)
        count++;
    return count;
}
