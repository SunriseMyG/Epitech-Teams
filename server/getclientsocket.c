/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** getclientsocket
*/

#include "../include/server.h"

int getclientsocket(server_t *server)
{
    return server->client_sockets[server->currentclient];
}

char *getteamuuid(server_t *server)
{
    return server->client_data[server->currentclient].team_uuid;
}

char *getchanneluuid(server_t *server)
{
    return server->client_data[server->currentclient].channel_uuid;
}

char *getthreaduuid(server_t *server)
{
    return server->client_data[server->currentclient].thread_uuid;
}
