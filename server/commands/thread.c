/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine [WSL : Ubuntu]
** File description:
** thread
*/

#include "../../include/server.h"

bool thread_already(server_t *server, char *thread_title)
{
    FILE *file = fopen("./database/threads", "r");
    char line[1024];
    char *thread_title_file;
    char *channel_uuid;

    while (fgets(line, sizeof(line), file)) {
        thread_title_file = strtok(line, "\t");
        strtok(NULL, "\t");
        strtok(NULL, "\t");
        strtok(NULL, "\t");
        channel_uuid = strtok(NULL, "\t");
        if (strcmp(thread_title_file, thread_title) == 0 &&
            strcmp(channel_uuid, getchanneluuid(server)) == 0) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

void create_thread(server_t *server, char **args)
{
    char *thread_title = args[0];
    char thread_body[256] = "";

    (void)server;
    if (thread_already(server, thread_title)) {
        send_log(getclientsocket(server), "ALREADY_CREATE %s",
            "anticrash");
        return;
    }
    for (int i = 1; args[i] != NULL; i++) {
        strcat(thread_body, args[i]);
        if (args[i + 1] != NULL)
            strcat(thread_body, " ");
    }
    stock_thread(server, thread_title, thread_body);
}

void stock_thread(server_t *server, char *thread_title, char *thread_body)
{
    char *thread_uuid = generate_uuid("xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx");
    FILE *file = fopen("./database/threads", "a");

    if (thread_body == NULL || strcmp(thread_body, "") == 0)
        thread_body = "\"\"";
    fprintf(file, "%s\t%s\t%ld\t%s\t%s\t%s\n", thread_title, thread_uuid,
        time(NULL), thread_body, getchanneluuid(server), server->client_data[
            server->currentclient].uuid);
    fclose(file);
    server_event_thread_created(getchanneluuid(server), thread_uuid,
        server->client_data[server->currentclient].uuid, thread_title,
        thread_body);
    send_log(getclientsocket(server), "CREATE_THREAD %s %s %ld %s %s",
        thread_uuid, server->client_data[server->currentclient].uuid,
        time(NULL), addquotes(thread_title), addquotes(thread_body));
}

void parse_thread_info(char *line, thread_t *thread)
{
    thread->thread_title = strtok(line, "\t");
    thread->thread_uuid = strtok(NULL, "\t");
    thread->thread_time = strtok(NULL, "\t");
    thread->thread_body = strtok(NULL, "\t");
}

void list_threads(server_t *server, char **args)
{
    FILE *file = fopen("./database/threads", "r");
    thread_t *thread = malloc(sizeof(thread_t));
    char line[1024];
    char *channel_uuid;

    (void)args;
    while (fgets(line, sizeof(line), file)) {
        parse_thread_info(line, thread);
        channel_uuid = strtok(NULL, "\t");
        if (strcmp(channel_uuid, getchanneluuid(server)) == 0) {
            send_log(getclientsocket(server), "LIST_THREAD %s %s %s %s %s",
                thread->thread_uuid, channel_uuid, thread->thread_time,
                thread->thread_title, thread->thread_body);
            usleep(1000);
        }
    }
    free(thread);
    fclose(file);
    return;
}
