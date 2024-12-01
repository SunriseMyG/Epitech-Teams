/*
** EPITECH PROJECT, 2024
** myteams [WSL: Ubuntu]
** File description:
** getuser
*/

#include "../../include/server.h"

char *generate_and_save_useruuid(char *username)
{
    char *uuid = generate_uuid("xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx");
    FILE *file = fopen("./database/users", "a");

    fprintf(file, "%s\t%s\n", username, uuid);
    fclose(file);
    return uuid;
}

char *get_useruuid(char *username)
{
    FILE *file = fopen("./database/users", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    char *useruuid = NULL;
    char *tempUsername;

    while (read != -1 && useruuid == NULL) {
        read = getline(&line, &len, file);
        tempUsername = strtok(line, "\t");
        if (tempUsername && strcmp(tempUsername, username) == 0) {
            useruuid = strdup(strtok(NULL, "\t"));
        }
    }
    free(line);
    fclose(file);
    if (useruuid == NULL)
        return generate_and_save_useruuid(username);
    useruuid[strlen(useruuid) - 1] = '\0';
    return useruuid;
}

char *get_username(char *uuid)
{
    FILE *file = fopen("./database/users", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    char *username = NULL;
    char *tempUUID;

    while (read != -1 && username == NULL) {
        read = getline(&line, &len, file);
        if (line == NULL || line[0] == '\n' || line[0] == '\0')
            break;
        tempUUID = strtok(strtok(line, "\t"), "\t");
        tempUUID[strcspn(tempUUID, "\n")] = 0;
        if (tempUUID && strcmp(tempUUID, uuid) == 0)
            username = strdup(strtok(line, "\t"));
    }
    free(line);
    fclose(file);
    printf("username: %s\n", username);
    return username;
}

void load_allusers()
{
    FILE *file = fopen("./database/users", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    char *username = "";
    char *uuid = "";

    printf("🛃 Loading all users\n");
    while (read != -1) {
        read = getline(&line, &len, file);
        username = strtok(line, "\t");
        username = removequotes(username);
        uuid = strtok(NULL, "\t");
        if (uuid) {
            uuid[strcspn(uuid, "\n")] = 0;
            server_event_user_loaded(uuid, username);
            printf("👤 %s loaded\n", username);
        }
    }
    fclose(file);
}
