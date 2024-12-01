/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** logout
*/

#include "../../include/server.h"

void logout(server_t *server, char **args)
{
    (void)args;
    send_log(getclientsocket(server), "LOGOUT %s %s",
        server->client_data[server->currentclient].username,
            server->client_data[server->currentclient].uuid);
    printf("👋 %s disconnected\n",
        server->client_data[server->currentclient].username);
    server_event_user_logged_out(
        server->client_data[server->currentclient].uuid);
    server->client_data[server->currentclient].username = NULL;
    server->client_data[server->currentclient].uuid[0] = '\0';
    server->client_data[server->currentclient].state = DEFAULT;
}
