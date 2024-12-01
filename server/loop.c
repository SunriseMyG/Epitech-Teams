/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** loop
*/

#include "../include/server.h"

void connection_socket(server_t *server)
{
    for (server->currentclient = 0; server->currentclient < FD_SETSIZE;
        server->currentclient++) {
        if (getclientsocket(server) == 0) {
            server->client_sockets[server->currentclient] =
                accept(server->socket, (struct sockaddr *)&server->addr,
                    (socklen_t *)&server->addrlen);
            printf("🌐 New connection, socket fd : %d, ip : %s, port : %d\n",
                getclientsocket(server),
                inet_ntoa(server->addr.sin_addr),
                ntohs(server->addr.sin_port));
            init_client(server, getclientsocket(server));
            FD_SET(getclientsocket(server), &server->readfds);
            server->client_nbr++;
            break;
        }
    }
}

void loop_socket(server_t *server)
{
    int activity;

    FD_ZERO(&server->readfds);
    FD_ZERO(&server->writefds);
    FD_SET(server->socket, &server->readfds);
    for (int i = 0; i < FD_SETSIZE; i++)
        if (server->client_sockets[i] > 0) {
            FD_SET(server->client_sockets[i], &server->readfds);
            FD_SET(server->client_sockets[i], &server->writefds);
        }
    activity = select(FD_SETSIZE, &server->readfds, &server->writefds,
        NULL, NULL);
    if (activity < 0) {
        perror("select");
        exit(EXIT_FAILURE);
    }
    if (FD_ISSET(server->socket, &server->readfds))
        connection_socket(server);
    receive_message(server);
}

void create_socket(server_t *server)
{
    while (1)
        loop_socket(server);
    close(server->socket);
    free(server);
}
