/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** messages
*/

#include "../../include/client.h"

void messages_log(char **args)
{
    args[2][strlen(args[2]) - 1] = '\0';
    client_private_message_print_messages(args[0], atoi(args[1]), args[2]);
}
