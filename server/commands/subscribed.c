/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** subscribed
*/

#include "../../include/server.h"

void get_info_team(server_t *server, char *uuid)
{
    FILE *file = fopen("./database/teams", "r");
    char line[256];
    char *team_name;
    char *team_uuid;
    char *team_desc;

    while (fgets(line, sizeof(line), file)) {
        team_name = strtok(line, "\t");
        team_uuid = strtok(NULL, "\t");
        team_desc = strtok(NULL, "\n");
        if (strcmp(team_uuid, uuid) == 0) {
            send_log(getclientsocket(server), "TEAM %s %s %s", team_uuid,
                addquotes(team_name), addquotes(team_desc));
            fclose(file);
            return;
        }
    }
    fclose(file);
}

void get_all_teams_of_user(server_t *server)
{
    FILE *file = fopen("./database/subscriptions", "r");
    char line[256];
    char **teams = malloc(sizeof(char *) * 256);
    int i = 0;
    char *team_uuid;
    char *client_uuid;

    while (fgets(line, sizeof(line), file)) {
        client_uuid = strtok(line, "\t");
        team_uuid = strtok(NULL, "\t");
        if (strcmp(client_uuid,
            server->client_data[server->currentclient].uuid) == 0) {
            teams[i] = team_uuid;
            i++;
        }
    }
    fclose(file);
    for (int j = 0; teams[j] != NULL; j++)
        get_info_team(server, teams[j]);
    free(teams);
}

void get_all_team(server_t *server, char **args)
{
    if (args[0] == NULL) {
        get_all_teams_of_user(server);
        return;
    }
    get_team(server, args[0]);
}

void append_subscribed_user(server_t *server, char *line, char *team_uuid,
    bool *response)
{
    char *client_uuid = strtok(line, "\t");
    char *current_team_uuid = strtok(NULL, "\t");
    char *client_username = strtok(NULL, "\n");

    (void)client_uuid;
    if (strcmp(current_team_uuid, team_uuid) == 0) {
        *response = true;
        send_log(getclientsocket(server), "USERS %s %s %d", client_uuid,
            addquotes(client_username),
            user_is_connected(server, client_uuid));
    }
}

void get_team(server_t *server, char *team_uuid)
{
    FILE *file = fopen("./database/subscriptions", "r");
    char line[256];
    bool response = false;

    while (fgets(line, sizeof(line), file)) {
        append_subscribed_user(server, line, team_uuid, &response);
    }
    fclose(file);
    if (!response)
        return send_log(getclientsocket(server), "UNKNOWN_TEAM %s",
            team_uuid);
}
