/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** un_subscribe
*/

#include "../../include/client.h"

void subscribe_success(char **args)
{
    args[0][strlen(args[0])] = '\0';
    args[1][strlen(args[1]) - 1] = '\0';
    client_print_subscribed(args[0], args[1]);
}

void unsubscribe_success(char **args)
{
    args[0][strlen(args[0])] = '\0';
    args[1][strlen(args[1]) - 1] = '\0';
    client_print_unsubscribed(args[0], args[1]);
}
