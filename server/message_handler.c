/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** message_handler
*/

#include "../include/server.h"

char *traitement(server_t *server, int i)
{
    if (server->valread == 0) {
        close(server->client_sockets[i]);
        server->client_sockets[i] = 0;
    } else {
        command_handler(server, strtrim(server->buffer));
    }
    return (server->buffer);
}

void manage_message(server_t *server, int i)
{
    server->currentclient = i;
    server->buffer = malloc(sizeof(char) * 1024);
    server->buffer = memset(server->buffer, 0, 1024);
    fcntl(server->client_sockets[i], F_SETFL,
        fcntl(server->client_sockets[i], F_GETFL, 0) | O_NONBLOCK);
    server->valread = myrecv(server->client_sockets[i],
        server->buffer, 1024);
    if (server->valread == -1 && (errno == EAGAIN ||
        errno == EWOULDBLOCK)) {
        free(server->buffer);
        return;
    }
    traitement(server, i);
    free(server->buffer);
}

void disconnection(server_t *server, int i)
{
    if (server->valread == 0)
        if (server->client_data[i].username != NULL)
            logout(server, NULL);
}

void receive_message(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(server->client_sockets[i], &server->readfds)) {
            manage_message(server, i);
            disconnection(server, i);
        }
    }
}
