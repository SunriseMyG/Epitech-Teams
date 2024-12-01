/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine [WSL : Ubuntu]
** File description:
** channel
*/

#include "../../include/server.h"

bool channel_already(server_t *server, char *channel_name)
{
    FILE *file = fopen("./database/channels", "r");
    char line[1024];
    char *channel_name_file;
    char *team_uuid;

    while (fgets(line, sizeof(line), file)) {
        channel_name_file = strtok(line, "\t");
        strtok(NULL, "\t");
        strtok(NULL, "\t");
        team_uuid = strtok(NULL, "\n");
        if (strcmp(channel_name_file, channel_name) == 0 &&
            strcmp(team_uuid, getteamuuid(server)) == 0) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

void create_channel(server_t *server, char **args)
{
    char *channel_name = args[0];
    char desc[256] = "";

    (void)server;
    if (channel_already(server, channel_name)) {
        send_log(getclientsocket(server), "ALREADY_CREATE %s",
            "anticrash");
        return;
    }
    for (int i = 1; args[i] != NULL; i++) {
        strcat(desc, args[i]);
        if (args[i + 1] != NULL)
            strcat(desc, " ");
    }
    stock_channel(server, channel_name, desc);
}

void stock_channel(server_t *server, char *channel_name, char *desc)
{
    char *channel_uuid = generate_uuid("xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx");
    FILE *file = fopen("./database/channels", "a");

    if (desc == NULL || strcmp(desc, "") == 0)
        desc = "\"\"";
    fprintf(file, "%s\t%s\t%s\t%s\n", channel_name, channel_uuid,
        desc, getteamuuid(server));
    fclose(file);
    server_event_channel_created(getteamuuid(server), channel_uuid,
        channel_name);
    send_log(getclientsocket(server), "CREATE_CHANNEL %s %s %s",
        channel_uuid, addquotes(channel_name), addquotes(desc));
}

void list_channels(server_t *server, char **args)
{
    FILE *file = fopen("./database/channels", "r");
    char line[1024];
    char *channel_name;
    char *channel_uuid;
    char *channel_desc;

    (void)args;
    while (fgets(line, sizeof(line), file)) {
        channel_name = strtok(line, "\t");
        channel_uuid = strtok(NULL, "\t");
        channel_desc = strtok(NULL, "\t");
        if (strcmp(strtok(NULL, "\n"), getteamuuid(server)) == 0)
            send_log(getclientsocket(server),
                "LIST_CHANNEL %s %s %s %s", addquotes(channel_name),
                channel_uuid, addquotes(channel_desc));
        usleep(1000);
    }
    fclose(file);
}
