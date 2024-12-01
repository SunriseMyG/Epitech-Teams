/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** users
*/

#include "../../include/server.h"

void users(server_t *server, char **args)
{
    char *uuid;
    char *username;
    FILE *file = fopen("./database/users", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    (void)args;
    while (true) {
        read = getline(&line, &len, file);
        if (read == -1)
            break;
        username = strtok(line, "\t");
        uuid = strtok(NULL, "\t");
        uuid[strlen(uuid) - 1] = '\0';
        send_log(getclientsocket(server), "USERS %s %s %d", uuid,
            addquotes(username), user_is_connected(server, uuid));
        usleep(10000);
    }
}
