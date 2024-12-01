/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** login
*/

#include "../../include/server.h"

bool check_login(server_t *server)
{
    if (server->client_data[server->currentclient].username != NULL) {
        send(getclientsocket(server),
            "Vous êtes déjà connecté\n", 29, 0);
        return false;
    }
    return true;
}

void set_uuid(server_t *server, char *username)
{
    char *generated_uuid;

    generated_uuid = get_useruuid(username);
    strcpy(server->client_data[server->currentclient].uuid, generated_uuid);
    server_event_user_logged_in(generated_uuid);
    free(generated_uuid);
}

bool check_username_is_valid(server_t *server, char *username)
{
    if (strlen(username) > MAX_NAME_LENGTH) {
        send(getclientsocket(server),
            "Le nom d'utilisateur est trop long\n", 35, 0);
        return false;
    }
    return true;
}

void send_data_login(server_t *server, char *username)
{
    send_log(getclientsocket(server), "LOGIN %s %s", addquotes(username),
        server->client_data[server->currentclient].uuid);
    printf("🎉 %s connected\n", removequotes(username));
    printf("🔑 UUID: %s\n",
        server->client_data[server->currentclient].uuid);
}

void login(server_t *server, char **args)
{
    char *username;

    if (args[0] == NULL || strlen(args[0]) == 0) {
        send(getclientsocket(server),
            "Veuillez entrer un nom d'utilisateur\n", 38, 0);
        return;
    }
    if (!check_username_is_valid(server, args[0]) || !check_login(server))
        return;
    username = strdup(args[0]);
    server->client_data[server->currentclient].username = username;
    set_uuid(server, username);
    send_data_login(server, username);
}
