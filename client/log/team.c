/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** team
*/

#include "../../include/client.h"

void info_teams(char **args)
{
    args[2][strlen(args[2]) - 1] = '\0';
    client_print_teams(args[0], args[1], args[2]);
}

void create_team(char **args)
{
    args[2][strlen(args[2]) - 1] = '\0';
    client_print_team_created(args[0], args[1], args[2]);
}
