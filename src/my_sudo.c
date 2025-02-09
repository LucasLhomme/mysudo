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

static int handle_error(char **argv)
{
    if (my_strcmp(argv[1], "cat") == 0 && argv[2] == NULL)
        return 84;
    if (my_strcmp(argv[1], "cat") == 0 && !fopen(argv[2], "r")) {
        my_printf("cat: %s: No such file or directory\n", argv[2]);
        return 84;
    }
    return 0;
}

static int execute_help(void)
{
    my_printf("usage: ./my_sudo -h\n");
    my_printf("usage: [-ugEs] [command [args ...]]\n");
    return 0;
}

int authenticate_user(int argc, char **argv, char *user)
{
    char **groups;

    if (handle_error(argv) == 84)
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
    if (verify_password(user) != 0)
        return 84;
    return 1;
}

static int check_help(int argc, char **argv)
{
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'h'
        && argv[1][2] == '\0') {
        execute_help();
        return 1;
    }
    return 0;
}

int execute_command(int argc, char **argv)
{
    uid_t uid = getuid();
    char *user = get_username(uid);
    int auth_result = authenticate_user(argc, argv, user);

    if (auth_result != 1)
        return auth_result;
    if (setuid(0) != 0)
        return 84;
    if (execvp(argv[1], &argv[1]) == -1) {
        my_printf("sudo: %s: command not found", argv[1]);
        return 84;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (check_help(argc, argv))
        return 0;
    if (argc < 2)
        return 84;
    if (command_exists(argv[1]) == 0) {
        my_printf("sudo: %s: command not found\n", argv[1]);
        return 84;
    }
    return execute_command(argc, argv);
}
