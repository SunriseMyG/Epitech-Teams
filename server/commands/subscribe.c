/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** subscribe
*/

#include "../../include/server.h"

void subscribe(server_t *server, char **args)
{
    if (args[0] == NULL) {
        send(getclientsocket(server),
            "Usage: /subscribe team_uuid\n", 28, 0);
        return;
    }
    subscribe_team(server, args[0]);
}

void save_and_log(FILE *file, char *client_uuid, char *team_uuid,
    char *username)
{
    fprintf(file, "%s\t%s\t%s\n", client_uuid, team_uuid, username);
    server_event_user_subscribed(team_uuid, client_uuid);
    fclose(file);
}

void subscribe_team(server_t *server, char *team_uuid)
{
    char *cli_uuid = server->client_data[server->currentclient].uuid;
    char *username = server->client_data[server->currentclient].username;
    FILE *file = fopen("./database/subscriptions", "a+");
    char line[256];

    if (!check_team_exist(team_uuid)) {
        fclose(file);
        send_log(getclientsocket(server), "UNKNOWN_TEAM %s", team_uuid);
        return;
    }
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, cli_uuid) && strstr(line, team_uuid)) {
            send(getclientsocket(server), "Team déjà suivis\n", 22, 0);
            fclose(file);
            return;
        }
    }
    save_and_log(file, cli_uuid, team_uuid, username);
    send_log(getclientsocket(server), "SUBSCRIBE %s %s", cli_uuid, team_uuid);
}

char *get_team_uuid_from_line(char *line)
{
    char *team_uuid;

    strtok(line, "\t");
    team_uuid = strtok(NULL, "\t");
    return team_uuid ? strdup(team_uuid) : NULL;
}

int check_team_exist(char *team_uuid)
{
    FILE *file = fopen("./database/teams", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int exists = 0;
    char *current_team_uuid;

    while (read != -1) {
        read = getline(&line, &len, file);
        line[strcspn(line, "\n")] = 0;
        current_team_uuid = get_team_uuid_from_line(line);
        if (current_team_uuid && strcmp(current_team_uuid, team_uuid) == 0)
            exists = 1;
        free(current_team_uuid);
        if (exists)
            break;
    }
    free(line);
    fclose(file);
    return exists;
}
