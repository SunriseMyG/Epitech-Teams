/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myftp
** File description:
** main
*/

#include "../include/server.h"

int main(int ac, char **av)
{
    server_t *server;

    if (av[1] == NULL)
        exit(84);
    server = iniserver_t(atoi(av[1]));
    (void)av;
    if (ac != 2 || strcmp(av[1], "-help") == 0)
        help();
    command_init(server);
    create_socket(server);
}
