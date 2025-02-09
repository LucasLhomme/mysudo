/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** check command existence
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <crypt.h>
#include "lib.h"
#include "my.h"

int check_path(char *cmd)
{
    return strchr(cmd, '/') && access(cmd, X_OK) == 0;
}

int search_path(char *cmd, char *path)
{
    char full_path[1024];
    char *paths = strdup(path);
    char *dir = strtok(paths, ":");

    if (!paths)
        return 0;
    while (dir) {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0) {
            free(paths);
            return 1;
        }
        dir = strtok(NULL, ":");
    }
    free(paths);
    return 0;
}

int command_exists(char *cmd)
{
    char *path = getenv("PATH");

    if (check_path(cmd))
        return 1;
    if (!path)
        return 0;
    return search_path(cmd, path);
}
