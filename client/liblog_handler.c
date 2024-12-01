/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** liblog_handler
*/

#include "../include/client.h"

void init_liblog(client_t *client)
{
    log_t funclog[] = {
        {"LOGIN", loginlog}, {"LOGOUT", logoutlog},
        {"UNKNOWN_USER", unknown_user}, {"UNKNOWN_TEAM", unknown_team},
        {"UNKNOWN_CHANNEL", unknown_channel},
        {"UNKNOWN_THREAD", unknown_thread}, {"SEND", receive_message_log},
        {"USER", user_log}, {"UNAUTHORIZED", unauthorized_user},
        {"MESSAGES", messages_log}, {"USERS", users_log},
        {"SUBSCRIBE", subscribe_success}, {"UNSUBSCRIBE", unsubscribe_success},
        {"TEAM", info_teams}, {"ALREADY_CREATE", already_exist},
        {"CREATE_TEAM", create_team}, {"CREATE_CHANNEL", create_channel},
        {"LIST_TEAM", list_team}, {"LIST_CHANNEL", list_channel},
        {"CREATE_THREAD", create_thread}, {"LIST_THREAD", list_thread},
        {"INFO_TEAM", info_team}, {"INFO_CHANNEL", info_channel},
        {"INFO_THREAD", info_thread}, {"CREATE_REPLY", create_reply}
    };

    client->nbr_logs = sizeof(funclog) / sizeof(log_t);
    client->logs = malloc(sizeof(funclog));
    for (int i = 0; i < client->nbr_logs; i++)
        client->logs[i] = funclog[i];
}

void liblog_handler(client_t *client, char *message)
{
    char *log = strtok(message, " ");
    char *command = strtok(NULL, " ");
    char *rest_of_message = strtok(NULL, "");
    char *full_message = malloc(strlen(command) + strlen(rest_of_message) + 2);
    char **split;

    (void)(log);
    for (int i = 0; command[i]; i++)
        command[i] = toupper(command[i]);
    sprintf(full_message, "%s %s", command, rest_of_message);
    split = removequotesfromargs(args_parser(full_message));
    free(full_message);
    for (int i = 0; i < client->nbr_logs; i++) {
        if (strcmp(client->logs[i].name, command) == 0) {
            client->logs[i].function(split);
            return;
        }
    }
    free_parsed_args(split);
    printf("Log not found : %s\n", command);
}
