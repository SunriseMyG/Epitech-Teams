/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** commandHandler
*/

#include "../include/server.h"

void command_init(server_t *server)
{
    command_t commands[] = {
        {"HELP", help_cli}, {"LOGIN", login}, {"LOGOUT", logout},
        {"USERS", users}, {"SEND", send_message}, {"USER", user},
        {"MESSAGES", get_all_message}, {"CREATE", create},
        {"SUBSCRIBE", subscribe}, {"UNSUBSCRIBE", unsubscribe},
        {"SUBSCRIBED", get_all_team}, {"USE", use}, {"LIST", list},
        {"INFO", info}
    };

    server->nbr_commands = sizeof(commands) / sizeof(command_t);
    server->commands = malloc(sizeof(commands));
    for (int i = 0; i < server->nbr_commands; i++) {
        server->commands[i] = commands[i];
    }
    printf("🚀 %d Commands Loadeds\n", server->nbr_commands);
}

char *beautify_command(char *command)
{
    char *new_command = malloc(sizeof(char) * (strlen(command) + 1));
    int i = 0;

    if (command[0] == '/')
        command++;
    for (int j = 0; command[j] != '\0'; j++) {
        if (command[j] == ' ')
            break;
        if (command[j] != '\t' && command[j] != '\n') {
            new_command[i] = toupper((unsigned char) command[j]);
            i++;
        }
    }
    new_command[i] = '\0';
    return (new_command);
}

bool islogged(server_t *server, char *command)
{
    if (strcmp(command, "LOGIN") == 0)
        return (true);
    if (server->client_data[server->currentclient].username == NULL) {
        send_log(getclientsocket(server), "UNAUTHORIZED %s", "stop crash");
        return (false);
    }
    return (true);
}

void command_handler(server_t *server, char *command)
{
    char **args;

    if (command == NULL || command[0] == '\0' || command[0] != '/')
        return;
    printf("🤖 Executing command: %s\n", command);
    args = args_parser(command);
    command = beautify_command(command);
    for (int i = 0; i < server->nbr_commands; i++) {
        if (strcmp(server->commands[i].name, command) == 0 &&
            islogged(server, command)) {
            server->commands[i].function(server, removequotesfromargs(args));
            return;
        }
    }
    send(getclientsocket(server), "Unknown command\n", 16, 0);
}
