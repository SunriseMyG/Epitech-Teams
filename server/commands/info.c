/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** info
*/

#include "../../include/server.h"

void info_default(server_t *server, char **args)
{
    char *uuid = server->client_data[server->currentclient].uuid;
    char *username = server->client_data[server->currentclient].username;

    (void)args;
    send_log(getclientsocket(server), "USER %s %s %d", uuid,
        addquotes(username), user_is_connected(server, uuid));
}

void info_team(server_t *server, char **args)
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
        if (strcmp(team_uuid, getteamuuid(server)) == 0) {
            send_log(getclientsocket(server), "INFO_TEAM %s %s %s",
                addquotes(team_name), team_uuid, addquotes(team_desc));
            fclose(file);
            return;
        }
    }
    fclose(file);
    send_log(getclientsocket(server), "UNKNOWN_TEAM %s", getteamuuid(server));
}

void info_channel(server_t *server, char **args)
{
    FILE *file = fopen("./database/channels", "r");
    char line[1024];
    char *channel_nam;
    char *channel_uuid;
    char *channel_desc;

    (void)args;
    while (fgets(line, sizeof(line), file)) {
        channel_nam = strtok(line, "\t");
        channel_uuid = strtok(NULL, "\t");
        channel_desc = strtok(NULL, "\t");
        if (strcmp(channel_uuid, getchanneluuid(server)) == 0) {
            send_log(getclientsocket(server), "INFO_CHANNEL %s %s %s",
                addquotes(channel_nam), channel_uuid, addquotes(channel_desc));
            return;
        }
    }
    fclose(file);
    send_log(getclientsocket(server), "UNKNOWN_CHANNEL %s",
        getchanneluuid(server));
}

void info_thread(server_t *server, char **args)
{
    FILE *file = fopen("./database/threads", "r");
    thread_t *thread = malloc(sizeof(thread_t));
    char line[1024];
    char *user_uuid;

    (void)args;
    while (fgets(line, sizeof(line), file)) {
        parse_thread_info(line, thread);
        user_uuid = strtok(strtok(NULL, "\t"), "\n");
        if (strcmp(thread->thread_uuid, getthreaduuid(server)) == 0) {
            send_log(getclientsocket(server), "INFO_THREAD %s %s %s %s %s",
                thread->thread_uuid, user_uuid, thread->thread_time,
                thread->thread_title, thread->thread_body);
            return;
        }
    }
    free(thread);
    fclose(file);
    send_log(getclientsocket(server), "UNKNOWN_THREAD %s",
        getthreaduuid(server));
}

void info(server_t *server, char **args)
{
    (void)args;
    if (server->client_data[server->currentclient].state == DEFAULT)
        info_default(server, args);
    if (server->client_data[server->currentclient].state == TEAM)
        info_team(server, args);
    if (server->client_data[server->currentclient].state == CHANNEL)
        info_channel(server, args);
    if (server->client_data[server->currentclient].state == THREAD)
        info_thread(server, args);
}
