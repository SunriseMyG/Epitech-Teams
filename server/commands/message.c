/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** send_message
*/

#include "../../include/server.h"

char *build_message(char **args)
{
    int total_length = 0;
    int i;
    char *message;

    for (i = 1; args[i] != NULL; i++) {
        total_length += strlen(args[i]) + 1;
    }
    message = malloc(total_length);
    if (message == NULL) {
        perror("malloc");
        return NULL;
    }
    strcpy(message, args[1]);
    for (i = 2; args[i] != NULL; i++) {
        strcat(message, " ");
        strcat(message, args[i]);
    }
    strcat(message, "\n");
    return message;
}

void log_message(server_t *server, char *message, int i)
{
    message[strcspn(message, "\n")] = '\0';
    send_log(server->client_data[i].socket, "SEND %s %s",
        server->client_data[server->currentclient].uuid,
            addquotes(message));
    server_event_private_message_sended(
        server->client_data[server->currentclient].uuid,
        server->client_data[i].uuid, message);
}

void send_message(server_t *server, char **args)
{
    char *user_uuid = args[0];
    char *message;

    if (args[0] == NULL || args[1] == NULL) {
        send(getclientsocket(server),
            "Usage: /message user_uuid message\n", 34, 0);
        return;
    }
    message = build_message(args);
    if (message == NULL)
        return;
    for (int i = 0; i < server->client_nbr; i++)
        if (strcmp(server->client_data[i].uuid, user_uuid) == 0) {
            stock_all_message(server, message, i);
            log_message(server, message, i);
            free(message);
            return;
        }
    send_log(getclientsocket(server), "UNKNOWN_USER %s", user_uuid);
}
