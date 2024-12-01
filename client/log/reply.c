/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine [WSL : Ubuntu]
** File description:
** reply
*/

#include "../../include/client.h"

void create_reply(char **args)
{
    args[3][strlen(args[3]) - 1] = '\0';
    client_print_reply_created(args[0], args[1], atoi(args[2]), args[3]);
}
