/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** the main file
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

char *extract_username(char *line, int uid)
{
    char *username = strtok(line, ":");
    char *uid_str = NULL;

    strtok(NULL, ":");
    uid_str = strtok(NULL, ":");
    if (uid_str != NULL && atoi(uid_str) == uid)
        return username;
    return NULL;
}

char *get_username(int uid)
{
    FILE *file = fopen("/etc/passwd", "r");
    char line[256];
    char *username;
    char *result = NULL;

    if (file == NULL)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        username = extract_username(line, uid);
        if (username != NULL) {
            result = strdup(username);
            break;
        }
    }
    fclose(file);
    return result;
}

int main(int argc, char **argv)
{
    uid_t uid = getuid();
    char *user = get_username(uid);

    printf("\n%s\n", user);
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'h'
        && argv[1][2] == '\0') {
        my_printf("usage: ./my_sudo -h\n");
        my_printf("usage: [-ugEs] [command [args ...]]\n");
        return 0;
    }
    printf("\n%s\n", user);
    if (verify_password("jawed") == 0) {
        printf("Authentication successful!\n");
    } else
        printf("Authentication failed.\n");
    if (setuid(0) != 0)
        return (84);
    execvp(argv[1], &argv[1]);
    return (84);
}
