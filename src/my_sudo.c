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

static int handle_error(int argc)
{
    if (argc < 2)
        return 84;
    return 0;
}

int execute_help(void)
{
    my_printf("usage: ./my_sudo -h\n");
    my_printf("usage: [-ugEs] [command [args ...]]\n");
    return 0;
}

int authenticate_user(int argc, char **argv, char *user)
{
    char **groups;

    if (handle_error(argc) == 84)
        return 84;
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'h'
        && argv[1][2] == '\0') {
        execute_help();
        return 0;
    }
    groups = parse_sudoers();
    if (check_group(groups, user) != 0) {
        my_printf("permission denied\n");
        return 84;
    }
    if (verify_password(user) != 0) {
        my_printf("Authentication failed.\n");
        return 0;
    }
    my_printf("Authentication successful!\n");
    return 1;
}

int main(int argc, char **argv)
{
    uid_t uid;
    char *user;
    int auth_result;

    uid = getuid();
    user = get_username(uid);
    auth_result = authenticate_user(argc, argv, user);
    if (auth_result != 1)
        return auth_result;
    if (setuid(0) != 0)
        return 84;
    if (execvp(argv[1], &argv[1]) == -1)
        my_printf("sudo: %s: command not found", argv[1]);
    return 0;
}
