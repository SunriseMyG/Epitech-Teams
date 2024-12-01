/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** help_cli
*/

#include "../../include/server.h"

void help_cli(server_t *server, char **args)
{
    char *help = "Commands:\n"
        "\t/help\n\t/login [user_name]\n\t/logout\n\t/users\n"
        "\t/user [user_uuid]\n"
        "\t/send [user_uuid] [message_body]\n"
        "\t/messages [user_uuid]\n"
        "\t/subscribe [team_uuid]\n"
        "\t/subscribed ?[team_uuid]\n"
        "\t/unsubscribe [team_uuid]\n"
        "\t/use ?[team_uuid] ?[channel_uuid] ?[thread_uuid]\n"
        "\t/create\n"
        "\t/list\n"
        "\t/info\n";

    (void)server;
    (void)args;
    send(getclientsocket(server), help, strlen(help), 0);
}
