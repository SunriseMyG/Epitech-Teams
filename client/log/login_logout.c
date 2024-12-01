/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** login
*/

#include "../../include/client.h"

void loginlog(char **args)
{
    args[1][strlen(args[1]) - 1] = '\0';
    client_event_logged_in(args[1], args[0]);
}

void logoutlog(char **args)
{
    args[1][strlen(args[1]) - 1] = '\0';
    client_event_logged_out(args[1], args[0]);
}
