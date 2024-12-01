/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myftp-lucka.valtriani
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "shared.h"
    #include "../libs/myteams/logging_server.h"

typedef enum {
    DEFAULT = 0,
    TEAM = 1,
    CHANNEL = 2,
    THREAD = 3
} set_t;

//Structure des data du client
typedef struct {
    char *username;
    char uuid[37];
    int socket;
    set_t state;
    char *team_uuid;
    char *channel_uuid;
    char *thread_uuid;
} client_data_t;

//Structure des messages
typedef struct {
    char *sender_uuid;
    char *receiver_uuid;
    char *message;
    int timestamp;
} message_t;

typedef struct {
    char *thread_title;
    char *thread_uuid;
    char *thread_time;
    char *thread_body;
} thread_t;

//Structure du serveur
typedef struct server_t server_t;

typedef void (*command_function_t)(server_t *, char **);

typedef struct {
    char *name;
    command_function_t function;
} command_t;

struct server_t {
    int port;
    //socket
    int socket;
    struct sockaddr_in addr;
    int addrlen;
    fd_set readfds;
    fd_set writefds;
    //client
    client_data_t client_data[FD_SETSIZE];
    int client_sockets[FD_SETSIZE];
    int currentclient;
    int client_nbr;
    //message received
    char *buffer;
    int valread;
    //all commands
    command_t *commands;
    int nbr_commands;
};

void help(void);
char *generate_uuid(const char *template);
server_t *iniserver_t(int port);
void init_client(server_t *server, int client_socket);
void create_socket(server_t *server);
void command_init(server_t *server);
void command_handler(server_t *server, char *command);
void receive_message(server_t *server);
int getclientsocket(server_t *server);
bool check_login(server_t *server);
char *build_message(char **args);
void stock_all_message(server_t *server, char *message, int i);
message_t *read_message_line(FILE *file, char **line, size_t *len);
void send_message_if_match(server_t *server, message_t *msg,
    char *user_uuid, char *args_uuid);
void create_team(server_t *server, char *team_name, char *desc);
char *team_exist(char *team_name);
void subscribe_team(server_t *server, char *team_uuid);
int check_team_exist(char *team_uuid);
void get_team(server_t *server, char *team_uuid);
void append_subscribed_user(server_t *server, char *line, char *team_uuid,
    bool *response);
void unsubscribe_team(server_t *server, char *team_uuid, char *user_uuid);
bool write_unsubscribed(FILE *file, FILE *tempfile, char *team_uuid,
    char *user_uuid);
char *addquotes(const char *arg);
bool user_is_connected(server_t *server, char *uuid);
bool channel_exist(char *team_uuid, char *channel_uuid);
bool thread_exist(char *team_uuid, char *channel_uuid, char *thread_uuid);
bool team_uuid_exist(char *team_uuid);
void get_state(server_t *server);
void create_a_team(server_t *server, char **args);
void create_channel(server_t *server, char **args);
void create_thread(server_t *server, char **args);
void create_reply(server_t *server, char **args);
void stock_channel(server_t *server, char *channel_team, char *desc);
void stock_thread(server_t *server, char *thread_title, char *message);
void stock_reply(server_t *server, char *comment_body);
int count_args(char **args);
void list_teams(server_t *server, char **args);
void list_channels(server_t *server, char **args);
void list_threads(server_t *server, char **args);
void list_replies(server_t *server, char **args);
char *getteamuuid(server_t *server);
char *getchanneluuid(server_t *server);
char *getthreaduuid(server_t *server);
void parse_thread_info(char *line, thread_t *thread);

// Commands
void help_cli(server_t *server, char **args);
void login(server_t *server, char **args);
void logout(server_t *server, char **args);
void users(server_t *server, char **args);
void send_message(server_t *server, char **args);
void user(server_t *server, char **args);
void get_all_message(server_t *server, char **args);
void subscribe(server_t *server, char **args);
void create(server_t *server, char **args);
void unsubscribe(server_t *server, char **args);
void get_all_team(server_t *server, char **args);
void use(server_t *server, char **args);
void list(server_t *server, char **args);
void info(server_t *server, char **args);

// Database

void initdb(void);
char *get_useruuid(char *username);
char *get_username(char *uuid);
void load_allusers(void);

// Lib log
void send_log(int socket, char *command, ...);

#endif /* !SERVER_H_ */
