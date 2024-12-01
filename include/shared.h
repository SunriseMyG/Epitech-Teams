/*
** EPITECH PROJECT, 2024
** B-NWP-400-NCE-4-1-myteams-steven.deffontaine
** File description:
** shared
*/

#ifndef SHARED_H_
    #define SHARED_H_

    #include <dlfcn.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <errno.h>
    #include <sys/select.h>
    #include <ctype.h>
    #include <fcntl.h>
    #include <stdbool.h>
    #include <dirent.h>
    #include <sys/mman.h>
    #include <sys/wait.h>
    #include <sys/types.h>
    #include <limits.h>
    #include <stdio.h>
    #include <time.h>
    #include <stdio.h>
    #include <stddef.h>
    #include <sys/stat.h>
    #include <stdarg.h>

    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

void *open_lib_myteams(void);
ssize_t myrecv(int sockfd, void *buf, size_t len);
char *strtrim(char *str);
char **quote_parser(char **args, bool keep_quotes);
char **args_parser(char *command);
char **removequotesfromargs(char **args);
char *removequotes(const char *arg);
void free_parsed_args(char **parsed);

#endif /* !SHARED_H_ */
