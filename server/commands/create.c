/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine [WSL : Ubuntu]
** File description:
** create
*/

#include "../../include/server.h"

void create_team(server_t *server, char *team_name, char *desc)
{
    char *team_uuid = generate_uuid("xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx");
    FILE *file = fopen("./database/teams", "a");

    fprintf(file, "%s\t%s\t%s\n", team_name, team_uuid, desc);
    fclose(file);
    server_event_team_created(team_uuid, team_name,
        server->client_data[server->currentclient].uuid);
    send_log(getclientsocket(server), "CREATE_TEAM %s %s %s",
        team_uuid, addquotes(team_name), addquotes(desc));
}

void create(server_t *server, char **args)
{
    if (server->client_data[server->currentclient].state == DEFAULT)
        create_a_team(server, args);
    if (server->client_data[server->currentclient].state == TEAM)
        create_channel(server, args);
    if (server->client_data[server->currentclient].state == CHANNEL)
        create_thread(server, args);
    if (server->client_data[server->currentclient].state == THREAD)
        create_reply(server, args);
}

bool team_already_exist(server_t *server, char *team_name)
{
    FILE *file = fopen("./database/teams", "r");
    char line[1024];
    char *team_name_file;

    while (fgets(line, sizeof(line), file)) {
        team_name_file = strtok(line, "\t");
        if (strcmp(team_name_file, team_name) == 0) {
            send_log(getclientsocket(server), "ALREADY_CREATE %s",
                "anticrash");
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

void create_a_team(server_t *server, char **args)
{
    char *team_name = args[0];
    char desc[256] = "";

    if (args[0] == NULL) {
        send_log(getclientsocket(server),
            "/create <team_name> <team_description>");
        return;
    }
    (void)server;
    if (team_already_exist(server, team_name))
        return;
    for (int i = 1; args[i] != NULL; i++) {
        strcat(desc, args[i]);
        if (args[i + 1] != NULL)
            strcat(desc, " ");
    }
    create_team(server, team_name, desc);
}
