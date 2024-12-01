/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine [WSL : Ubuntu]
** File description:
** list
*/

#include "../../include/server.h"

void list(server_t *server, char **args)
{
    if (server->client_data[server->currentclient].state == DEFAULT)
        list_teams(server, args);
    if (server->client_data[server->currentclient].state == TEAM)
        list_channels(server, args);
    if (server->client_data[server->currentclient].state == CHANNEL)
        list_threads(server, args);
    if (server->client_data[server->currentclient].state == THREAD)
        list_replies(server, args);
}

void list_teams(server_t *server, char **args)
{
    FILE *file = fopen("./database/teams", "r");
    char line[1024];
    char *team_name;
    char *team_uuid;
    char *team_desc;

    (void)args;
    while (fgets(line, sizeof(line), file)) {
        team_name = strtok(line, "\t");
        team_uuid = strtok(NULL, "\t");
        team_desc = strtok(NULL, "\n");
        send_log(getclientsocket(server), "LIST_TEAM %s %s %s",
            addquotes(team_name), team_uuid, addquotes(team_desc));
        usleep(1000);
    }
    fclose(file);
    return;
}
