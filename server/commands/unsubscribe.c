/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** unsubscribe
*/

#include "../../include/server.h"

void unsubscribe(server_t *server, char **args)
{
    char *user_uuid = server->client_data[server->currentclient].uuid;

    if (args[0] == NULL) {
        send(getclientsocket(server),
            "Usage: /unsubscribe team_uuid\n", 29, 0);
        return;
    }
    unsubscribe_team(server, args[0], user_uuid);
}

bool write_unsubscribed(FILE *file, FILE *tempfile, char *team_uuid,
    char *user_uuid)
{
    char line[256];
    char *file_team_uuid;
    char *file_user_uuid;
    bool found = false;
    char temp_line[256];

    while (fgets(line, sizeof(line), file)) {
        strcpy(temp_line, line);
        file_user_uuid = strtok(temp_line, "\t");
        file_team_uuid = strtok(NULL, "\t");
        if (strcmp(file_user_uuid, user_uuid) == 0
            && strcmp(file_team_uuid, team_uuid) == 0)
            found = true;
        else
            fputs(line, tempfile);
    }
    return found;
}

void unsubscribe_team(server_t *server, char *team_uuid, char *user_uuid)
{
    FILE *file = fopen("./database/subscriptions", "r");
    FILE *tempfile = fopen("./database/temp", "w");
    bool found = write_unsubscribed(file, tempfile, team_uuid, user_uuid);

    fclose(file);
    fclose(tempfile);
    remove("./database/subscriptions");
    rename("./database/temp", "./database/subscriptions");
    if (found) {
        server_event_user_unsubscribed(team_uuid, user_uuid);
        send_log(getclientsocket(server), "UNSUBSCRIBE %s %s",
            user_uuid, team_uuid);
    } else
        send_log(getclientsocket(server), "UNKNOWN_TEAM %s", team_uuid);
}
