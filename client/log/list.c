/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** list
*/

#include "../../include/client.h"

void list_team(char **args)
{
    args[2][strlen(args[2]) - 1] = '\0';
    client_print_teams(args[0], args[1], args[2]);
}

void list_channel(char **args)
{
    client_print_channel(args[0], args[1], args[2]);
}

void list_thread(char **args)
{
    args[4][strlen(args[4]) - 1] = '\0';
    client_channel_print_threads(args[0], args[1], atoi(args[2]),
        args[3], args[4]);
}
