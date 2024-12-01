/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myftp
** File description:
** main
*/

#include "../include/client.h"

void check_port(char *port)
{
    if (access(port, F_OK) == 0) {
        printf("Invalid port1.\n");
        exit(84);
    }
    if (atoi(port) < 1 || atoi(port) > 65535) {
        printf("Invalid port2.\n");
        exit(84);
    }
    if (atoi(port) == 0) {
        printf("Invalid port3.\n");
        exit(84);
    }
    return;
}

void receive_message(client_t *client)
{
    char buffer[1024];

    memset(buffer, 0, 1024);
    read(client->socket, buffer, 1024);
    receive_message_handler(client, buffer);
}

void send_message(client_t *client)
{
    char buffer[1024];

    memset(buffer, 0, 1024);
    read(STDIN_FILENO, buffer, 1024);
    send(client->socket, buffer, strlen(buffer), 0);
}

void manage_clienserver_t(client_t *client)
{
    fd_set readfds;
    fd_set writefds;

    init_liblog(client);
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(client->socket, &readfds);
        FD_ZERO(&writefds);
        FD_SET(client->socket, &writefds);
        select(client->socket + 1, &readfds, &writefds, NULL, NULL);
        if (FD_ISSET(STDIN_FILENO, &readfds)
            && FD_ISSET(client->socket, &writefds))
            send_message(client);
        if (FD_ISSET(client->socket, &readfds))
            receive_message(client);
    }
}

int main(int ac, char **av)
{
    int connection_status;
    client_t *client = malloc(sizeof(client_t));

    if (ac != 3 || strcmp(av[1], "-help") == 0)
        help();
    check_port(av[2]);
    client->socket = socket(AF_INET, SOCK_STREAM, 0);
    client->addr.sin_family = AF_INET;
    client->addr.sin_port = htons(atoi(av[2]));
    client->addr.sin_addr.s_addr = inet_addr(av[1]);
    connection_status = connect(client->socket,
        (struct sockaddr *)&client->addr, sizeof(client->addr));
    if (connection_status == -1) {
        printf("Connection failed.\n");
        exit(1);
    } else
        printf("Connection successful.\n");
    manage_clienserver_t(client);
    return 0;
}
