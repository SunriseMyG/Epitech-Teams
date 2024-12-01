/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** init
*/

#include "../include/server.h"

void *bind_socket(server_t *server)
{
    if (bind(server->socket, (struct sockaddr *)&server->addr,
        sizeof(server->addr)) < 0) {
        perror("bind failed");
        exit(84);
    }
    if (listen(server->socket, 3) < 0) {
        perror("listen");
        exit(84);
    }
    return server;
}

server_t *iniserver_t(int port)
{
    server_t *server = malloc(sizeof(server_t));

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == 0) {
        perror("socket failed");
        exit(84);
    }
    server->port = port;
    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->addr.sin_port = htons(server->port);
    bind_socket(server);
    server->addrlen = sizeof(server->addr);
    initdb();
    load_allusers();
    return server;
}

void init_client(server_t *server, int client_socket)
{
    server->client_data[server->currentclient].socket = client_socket;
}
