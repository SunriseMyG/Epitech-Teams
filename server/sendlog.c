/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** sendlog
*/

#include "../include/server.h"

void send_log(int socket, char *command, ...)
{
    va_list args;
    char *log = malloc(1024);

    strcpy(log, "LOG ");
    va_start(args, command);
    vsprintf(log + 4, command, args);
    va_end(args);
    strcat(log, "\n");
    printf("📩 Send LOG : %s", log);
    send(socket, log, strlen(log), 0);
    free(log);
}
