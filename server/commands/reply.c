/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine [WSL : Ubuntu]
** File description:
** reply
*/

#include "../../include/server.h"

void create_reply(server_t *server, char **args)
{
    char *comment_body = args[0];

    (void)server;
    for (int i = 1; args[i] != NULL; i++) {
        strcat(comment_body, args[i]);
        if (args[i + 1] != NULL)
            strcat(comment_body, " ");
    }
    stock_reply(server, comment_body);
}

void stock_reply(server_t *server, char *comment_body)
{
    char *comment_uuid = generate_uuid("xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx");
    FILE *file = fopen("./database/replies", "a");

    if (comment_body == NULL || strcmp(comment_body, "") == 0)
        comment_body = "\"\"";
    fprintf(file, "%s\t%s\t%ld\t%s\t%s\t%s\n", comment_body, comment_uuid,
        time(NULL), getthreaduuid(server),
        server->client_data[server->currentclient].uuid,
        getchanneluuid(server));
    fclose(file);
    server_event_reply_created(getthreaduuid(server),
        server->client_data[server->currentclient].uuid, comment_body);
    send_log(getclientsocket(server), "CREATE_REPLY %s %s %ld %s",
        getthreaduuid(server), server->client_data[server->currentclient].uuid,
        time(NULL), addquotes(comment_body));
}

void list_replies(server_t *server, char **args)
{
    (void)server;
    (void)args;
    return;
}
