/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include "shared.h"
    #include "../libs/myteams/logging_client.h"

typedef struct client_t client_t;

typedef void (*log_function_t)(char **);

typedef struct {
    char *name;
    log_function_t function;
} log_t;

struct client_t {
    int socket;
    struct sockaddr_in addr;
    log_t *logs;
    int nbr_logs;
    char *username;
};

void help(void);
void receive_message_handler(client_t *client, char *message);
void liblog_handler(client_t *client, char *message);
void init_liblog(client_t *client);

// Log functions
void loginlog(char **args);
void logoutlog(char **args);
void unknown_user(char **args);
void receive_message_log(char **args);
void user_log(char **args);
void unauthorized_user(char **args);
void messages_log(char **args);
void users_log(char **args);
void unknown_team(char **args);
void unknown_channel(char **args);
void unknown_thread(char **args);
void subscribe_success(char **args);
void unsubscribe_success(char **args);
void info_teams(char **args);
void already_exist(char **args);
void create_team(char **args);
void create_channel(char **args);
void create_thread(char **args);
void create_reply(char **args);
void list_team(char **args);
void list_channel(char **args);
void list_thread(char **args);
void info_team(char **args);
void info_channel(char **args);
void info_thread(char **args);

#endif /* !CLIENT_H_ */
