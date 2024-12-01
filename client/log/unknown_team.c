/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** unknown_team
*/

#include "../../include/client.h"

void unknown_team(char **args)
{
    args[0][strlen(args[0]) - 1] = '\0';
    client_error_unknown_team(args[0]);
}

void unknown_channel(char **args)
{
    args[0][strlen(args[0]) - 1] = '\0';
    client_error_unknown_channel(args[0]);
}

void unknown_thread(char **args)
{
    args[0][strlen(args[0]) - 1] = '\0';
    client_error_unknown_thread(args[0]);
}

void already_exist(char **args)
{
    (void)args;
    client_error_already_exist();
}
