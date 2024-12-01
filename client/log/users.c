/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** users
*/

#include "../../include/client.h"

void user_log(char **args)
{
    client_print_user(args[0], removequotes(args[1]), atoi(args[2]));
}

void users_log(char **args)
{
    client_print_users(args[0], removequotes(args[1]), atoi(args[2]));
}
