/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** handle user perm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "my.h"
#include "lib.h"

char **parse_sudoers(void)
{
    char user[50];
    FILE *file = fopen("/etc/sudoers", "r");
    char line[256];
    char **users = malloc(257 * sizeof(char *) );
    int i = 0;

    if (file == NULL || !users)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == 'D' || line[0] == '@')
            continue;
        if (sscanf(line, "%49s ALL=(ALL) ALL", user) == 1) {
            users[i] = strdup(user);
            i++;
        }
    }
    if (users == NULL)
        return NULL;
    users[i] = NULL;
    fclose(file);
    return users;
}

int check_group(char **group, char *user)
{
    char **user_groups = user_group(user);

    if (user_groups == NULL || group == NULL)
        return 84;
    for (int i = 0; group[i] != NULL; i++) {
        for (int k = 0; user_groups[k] != NULL; k++) {
            if (my_strcmp(group[i], user_groups[k]) == 0)
                return 0;
        }
    }
    return 84;
}

char **user_group(char *user)
{
    FILE *file = fopen("/etc/group", "r");
    char line[256];
    char *group = NULL;
    char **user_groups = malloc(256 * sizeof(char *));
    char **members;
    char *users_in_group;
    int j = 0;

    if (!file)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        group = strtok(line, ":");
        strtok(NULL, ":");
        strtok(NULL, ":");
        users_in_group = strtok(NULL, ":");
        if (!users_in_group)
            continue;
        members = my_str_to_word_array(users_in_group);
        for (int i = 0; members[i] != NULL; i++) {
            if (my_strcmp(user, members[i]) == 0) {
                user_groups[j] = my_strdup(group);
                j++;
            }
        }
    }
    user_groups[j] = NULL;
    fclose(file);
    return user_groups;
}