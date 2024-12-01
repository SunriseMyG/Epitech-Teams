/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myftp
** File description:
** help
*/

#include "../include/client.h"

void help(void)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip");
    printf("\tis the server ip address on which the server socket listens\n");
    printf("\tport\tis the port number on which the server socket listens\n");
    exit(84);
}
