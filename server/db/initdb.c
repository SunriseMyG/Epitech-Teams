/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** initdb
*/

#include "../../include/server.h"

void initdb(void)
{
    char *checkfile[] = {"users", "messages", "teams", "subscriptions",
        "channels", "threads", "replies"};
    char filepath[256];
    FILE *file;

    mkdir("./database", 0777);
    printf("🔗 Checking database\n");
    for (int i = 0; i < 7; i++) {
        sprintf(filepath, "./database/%s", checkfile[i]);
        if (access(filepath, F_OK) == -1) {
            file = fopen(filepath, "w");
            printf("📁 %s created\n", checkfile[i]);
            fclose(file);
        } else {
            printf("📁 %s already exist\n", checkfile[i]);
        }
    }
}
