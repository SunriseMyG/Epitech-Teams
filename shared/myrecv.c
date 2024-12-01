/*
** EPITECH PROJECT, 2024
** myftp [WSL: Ubuntu]
** File description:
** myrecv
*/

#include "../include/shared.h"

ssize_t myrecv(int sockfd, void *buf, size_t len)
{
    ssize_t bytesRead = read(sockfd, buf, len);

    return bytesRead;
}
