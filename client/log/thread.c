/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine [WSL : Ubuntu]
** File description:
** thread
*/

#include "../../include/client.h"

void create_thread(char **args)
{
    args[4][strlen(args[4]) - 1] = '\0';
    for (int i = 0; i < 5; i++)
        printf("%s\n", args[i]);
    client_print_thread_created(args[0], args[1],
        atoi(args[2]), args[3], args[4]);
}
