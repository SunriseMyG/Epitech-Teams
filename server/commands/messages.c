/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine [WSL : Ubuntu]
** File description:
** messages
*/

#include "../../include/server.h"

void stock_all_message(server_t *server, char *message, int i)
{
    FILE *file = fopen("./database/messages", "a");

    fprintf(file, "%s\t%s\t%ld\t%s",
        server->client_data[server->currentclient].uuid,
        server->client_data[i].uuid, time(NULL), message);
    fclose(file);
    return;
}

message_t *read_message_line(FILE *file, char **line, size_t *len)
{
    ssize_t read = getline(line, len, file);
    message_t *msg = malloc(sizeof(message_t));

    if (read == -1)
        return NULL;
    msg->sender_uuid = strtok(*line, "\t");
    msg->receiver_uuid = strtok(NULL, "\t");
    msg->timestamp = atoi(strtok(NULL, "\t"));
    msg->message = strtok(NULL, "\t");
    return msg;
}

void send_message_if_match(server_t *server, message_t *msg,
    char *user_uuid, char *args_uuid)
{
    if ((strcmp(msg->sender_uuid, user_uuid) == 0 &&
        strcmp(msg->receiver_uuid, args_uuid) == 0) ||
        (strcmp(msg->receiver_uuid, user_uuid) == 0 &&
        strcmp(msg->sender_uuid, args_uuid) == 0)) {
        msg->message[strcspn(msg->message, "\n")] = '\0';
        send_log(getclientsocket(server), "MESSAGES %s %d %s",
            msg->sender_uuid, msg->timestamp, addquotes(msg->message));
        usleep(1000);
        }
}

bool loop_messages(server_t *server, message_t *msg, char *user_uuid,
    char **args)
{
    if (msg->sender_uuid == NULL || msg->receiver_uuid == NULL ||
        msg->message == NULL) {
        free(msg);
        return false;
    } else {
        send_message_if_match(server, msg, user_uuid, args[0]);
        free(msg);
        return true;
    }
}

void get_all_message(server_t *server, char **args)
{
    FILE *file = fopen("./database/messages", "r");
    char *line = NULL;
    size_t len = 0;
    char *user_uuid;
    message_t *msg;
    bool found = false;
    bool temp = false;

    user_uuid = server->client_data[server->currentclient].uuid;
    msg = read_message_line(file, &line, &len);
    while (msg != NULL) {
        temp = loop_messages(server, msg, user_uuid, args);
        msg = read_message_line(file, &line, &len);
        if (!found && temp)
            found = true;
    }
    if (!found && args[0] != NULL && get_username(args[0]) == NULL)
        send_log(getclientsocket(server), "UNKNOWN_USER %s", args[0]);
    fclose(file);
    free(line);
}
