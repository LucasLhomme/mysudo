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

    if (file == NULL)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        username = extract_username(line, uid);
        if (username != NULL) {
            fclose(file);
            return username;
        }
    }
    fclose(file);
    return NULL;
}

int is_user_in_sudoers(char *user)
{
    FILE *file = fopen("/etc/sudoers", "r");
    char line[256];

    if (!file)
        return (0);
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, user) && strstr(line, "ALL=(ALL) ALL")) {
            fclose(file);
            return (1);
        }
    }
    fclose(file);
    return (0);
}

int main(int argc, char **argv)
{
    uid_t uid = getuid();
    char *user = get_username(uid);

    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'h'
        && argv[1][2] == '\0') {
        my_printf("usage: ./my_sudo -h\n");
        my_printf("usage: [-ugEs] [command [args ...]]\n");
        return 0;
    }
    if (!user || !is_user_in_sudoers(user))
        return (84);
    if (verify_password("jawed") == 0) {
        printf("Authentication successful!\n");
    } else
        printf("Authentication failed.\n");
    if (setuid(0) != 0)
        return (84);
    execvp(argv[1], &argv[1]);
    return (84);
}
