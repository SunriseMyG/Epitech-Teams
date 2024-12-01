/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** receive_message_handler
*/

#include "../include/client.h"

void receive_message_handler(client_t *client, char *message)
{
    char *copymessage = strdup(message);
    char *firstword = strtok(copymessage, " ");

    if (firstword == NULL) {
        printf("Server disconnected\n");
        exit(0);
    }
    if (strcmp(firstword, "LOG") == 0) {
        liblog_handler(client, message);
    } else {
        printf("%s", message);
    }
    free(copymessage);
}
