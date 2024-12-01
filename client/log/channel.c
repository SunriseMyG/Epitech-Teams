/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** channel
*/

#include "../../include/client.h"

void create_channel(char **args)
{
    args[2][strlen(args[2]) - 1] = '\0';
    client_print_channel_created(args[0], args[1], args[2]);
}
