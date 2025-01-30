/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** parse file
*/

#include "lib.h"
#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "my.h"

char **parse_sudoers(void)
{
    char user[50];
    FILE *file = fopen("/etc/sudoers", "r");
    char line[256];
    char **groups = malloc(256 * sizeof(char *));
    int i = 0;

    if (file == NULL)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == 'D')
            continue;
        if (sscanf(line, "%49s ALL=(ALL) ALL", user) == 1) {
            groups[i] = strdup(user);
            i++;
        }
    }
    fclose(file);
    groups[i] = NULL;
    return groups;
}
