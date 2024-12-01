/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** user
*/


#include "../../include/server.h"

bool user_is_connected(server_t *server, char *uuid)
{
    for (int i = 0; i < server->client_nbr; i++) {
        if (strcmp(server->client_data[i].uuid, uuid) == 0)
            return (true);
    }
    return (false);
}

char *get_username_user(server_t *server, char *uuid)
{
    for (int i = 0; i < server->client_nbr; i++) {
        if (strcmp(server->client_data[i].uuid, uuid) == 0)
            return (server->client_data[i].username);
    }
    return get_username(uuid);
}

void concat_msg_and_send(server_t *server, char *uuid,
    char *username, bool isconnected)
{
    send_log(getclientsocket(server), "USER %s %s %d", uuid,
        addquotes(username), isconnected);
}

void user(server_t *server, char **args)
{
    char *username;

    if (args[0] == NULL) {
        send(getclientsocket(server), "Vous n'avez pas renseigné d'uuid\n",
            33, 0);
        return;
    }
    username = get_username_user(server, args[0]);
    if (username == NULL) {
        send_log(getclientsocket(server), "UNKNOWN_USER %s", args[0]);
        return;
    }
    concat_msg_and_send(server, args[0], username,
        user_is_connected(server, args[0]));
}
