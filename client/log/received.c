/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** received
*/

#include "../../include/client.h"

void receive_message_log(char **args)
{
    args[0][strlen(args[0]) - 1] = '\0';
    args[1][strlen(args[1]) - 1] = '\0';
    client_event_private_message_received(args[0], args[1]);
}