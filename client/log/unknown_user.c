/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** unknow_user
*/

#include "../../include/client.h"

void unknown_user(char **args)
{
    args[0][strlen(args[0]) - 1] = '\0';
    client_error_unknown_user(args[0]);
}
