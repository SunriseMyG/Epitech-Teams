/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** uuid
*/

#include "../include/server.h"

char *generate_uuid(const char *template)
{
    char *result = (char *)malloc(sizeof(char) * (strlen(template) + 1));
    int value;

    if (result == NULL)
        return NULL;
    srand((unsigned int)time(NULL));
    for (int i = 0; template[i] != '\0'; ++i) {
        if (template[i] == 'x') {
            value = rand() % 16;
            sprintf(result + i, "%x", value);
        }
        if (template[i] == 'y') {
            value = 8 + rand() % 4;
            sprintf(result + i, "%x", value);
        }
        if (template[i] != 'x' && template[i] != 'y')
            result[i] = template[i];
    }
    result[strlen(template)] = '\0';
    return result;
}
