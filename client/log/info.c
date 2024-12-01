/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** info
*/

#include "../../include/client.h"

void info_team(char **args)
{
    args[2][strlen(args[2]) - 1] = '\0';
    client_print_team(args[0], args[1], args[2]);
}

void info_channel(char **args)
{
    args[2][strlen(args[2]) - 1] = '\0';
    client_print_channel(args[0], args[1], args[2]);
}

void info_thread(char **args)
{
    args[4][strlen(args[4]) - 1] = '\0';
    client_print_thread(args[0], args[1], atoi(args[2]), args[3], args[4]);
}
