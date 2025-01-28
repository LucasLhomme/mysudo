/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** the main file
*/

#include "lib.h"
#include <crypt.h>

char **parse_sudoers(void)
{
    char user[50];
    FILE *file = fopen("/etc/sudoers", "r");
    char line[256];
    char **users = malloc(256 * sizeof(char *));
    int i = 0;

    if (file == NULL)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == 'D')
            continue;
    if (sscanf(line, "%49s ALL=(ALL) ALL", user) == 1) {
            users[i] = strdup(user);
            i++;
        }
        my_printf("%s\n", user);
    }
    fclose(file);
    return users;
}

int main(int argc, char **argv)
{
    char **users = malloc(256 * sizeof(char *));

    if (users == NULL)
        return 84;
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'h'
        && argv[1][2] == '\0') {
        my_printf("usage: ./my_sudo -h\n");
        my_printf("usage: [-ugEs] [command [args ...]]\n");
    }
    users = parse_sudoers();
    if (users == NULL)
        return 84;
}
