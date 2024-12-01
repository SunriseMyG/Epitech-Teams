/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** set
*/

#include "../../include/server.h"

void use(server_t *server, char **args)
{
    int arg_count = 0;

    while (args[arg_count] != NULL)
        arg_count++;
    server->client_data[server->currentclient].state = DEFAULT;
    if (arg_count == 0)
        server->client_data[server->currentclient].state = DEFAULT;
    if (arg_count == 1 && team_uuid_exist(args[0])) {
        server->client_data[server->currentclient].state = TEAM;
        server->client_data[server->currentclient].team_uuid = args[0];
    }
    if (arg_count == 2 && channel_exist(args[0], args[1])) {
        server->client_data[server->currentclient].state = CHANNEL;
        server->client_data[server->currentclient].channel_uuid = args[1];
    }
    if (arg_count == 3 && thread_exist(args[0], args[1], args[2])) {
        server->client_data[server->currentclient].state = THREAD;
        server->client_data[server->currentclient].thread_uuid = args[2];
    }
    get_state(server);
}

void get_state(server_t *server)
{
    switch (server->client_data[server->currentclient].state) {
        case DEFAULT:
            printf("👀 Etat du client %s : DEFAULT\n",
                server->client_data[server->currentclient].username);
            break;
        case TEAM:
            printf("👀 Etat du client %s : TEAM\n",
                server->client_data[server->currentclient].username);
            break;
        case CHANNEL:
            printf("👀 Etat du client : CHANNEL\n");
            break;
        case THREAD:
            printf("👀 Etat du client : THREAD\n");
            break;
        default:
            printf("👀 Etat du client : UNKNOWN\n");
    }
    return;
}

bool channel_exist(char *team_uuid, char *channel_uuid)
{
    bool channel_exists = false;
    FILE *file = fopen("./database/channels", "r");
    char line[256];
    char *current_uuid;

    while (fgets(line, sizeof(line), file) != NULL) {
        strtok(line, "\t");
        current_uuid = strtok(NULL, "\t");
        if (current_uuid != NULL && strcmp(current_uuid, channel_uuid) == 0) {
            channel_exists = true;
            break;
        }
    }
    fclose(file);
    if (team_uuid_exist(team_uuid))
        return channel_exists;
    else
        return false;
}

bool thread_exist(char *team_uuid, char *channel_uuid, char *thread_uuid)
{
    bool thread_exists = false;
    bool team_exists = team_uuid_exist(team_uuid);
    bool channel_exists = channel_exist(team_uuid, channel_uuid);
    FILE *file = fopen("./database/threads", "r");
    char line[256];
    char *current_uuid;

    while (fgets(line, sizeof(line), file) != NULL) {
        strtok(line, "\t");
        current_uuid = strtok(NULL, "\t");
        if (current_uuid != NULL && strcmp(current_uuid, thread_uuid) == 0) {
            thread_exists = true;
            break;
        }
    }
    fclose(file);
    if (!team_exists && channel_exists && thread_exists)
        thread_exists = false;
    return thread_exists;
}

bool team_uuid_exist(char *team_uuid)
{
    FILE *file = fopen("./database/teams", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    char *current_uuid;
    bool exists = false;

    while (read != -1) {
        read = getline(&line, &len, file);
        strtok(line, "\t");
        current_uuid = strtok(NULL, "\t");
        if (current_uuid != NULL && strcmp(current_uuid, team_uuid) == 0) {
            exists = true;
            break;
        }
    }
    fclose(file);
    free(line);
    return exists;
}
