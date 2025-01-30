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

int verify_password(char *user)
{
    char *entered_pass = "$6$xyz$dummyhash";
    char *stored_pass[256];
    int attempts = 0;

    while (attempts < 3) {
        write(1, "[my_sudo] password: ", 20);
        entered_pass = getpass("");
        if (!strcmp(crypt(entered_pass, stored_pass), stored_pass))
            return (0);
        attempts++;
        write(2, "Incorrect password. Attempts left: ", 35);
        dprintf(2, "%d\n", 3 - attempts);
    }
    return (-1);
}

int main(int argc, char **argv)
{
    uid_t uid = getuid();
    char *user = get_username(uid);

    if (!user || !is_user_in_sudoers(user)) {
        dprintf(2, "User is not in sudoers.\n");
        return (84);
    }
    if (verify_password(user) != 0) {
        write(2, "Authentication failed.\n", 24);
        return (84);
    }
    if (setuid(0) != 0) {
        perror("setuid");
        return (84);
    }
    execvp(argv[1], &argv[1]);
    perror("execvp");
    return (84);
}
