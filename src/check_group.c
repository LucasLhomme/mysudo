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
    char **users = malloc(256 * sizeof(char *));
    int i = 0;

    if (file == NULL)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n' ||
            line[0] == 'D' || line[0] == '@')
            continue;
        if (sscanf(line, "%49s ALL=(ALL) ALL", user) == 1) {
            users[i] = strdup(user);
            i++;
        }
    }
    users[i] = NULL;
    fclose(file);
    return users;
}

int verify_group(char *sudo_group, char **user_groups)
{
    for (int k = 0; user_groups[k] != NULL; k++) {
        if (my_strcmp(sudo_group, user_groups[k]) == 0)
            return 1;
    }
    return 0;
}

int check_group(char **group, char *user)
{
    char **user_groups = user_group(user);
    char *sudo_group;

    if (user_groups == NULL || group == NULL)
        return 84;
    for (int i = 0; group[i] != NULL; i++) {
        sudo_group = (group[i][0] == '%') ? group[i] + 1 : group[i];
        if (verify_group(sudo_group, user_groups) == 1)
            return 0;
    }
    my_printf("%s is not in the my_sudoers file.", user);
    return 84;
}

group_t get_group_info(char *line)
{
    group_t info;

    info.group = strtok(line, ":");
    strtok(NULL, ":");
    strtok(NULL, ":");
    info.members = my_str_to_word_array(strtok(NULL, ":"));
    return info;
}

static int user_list(char *user, char **members)
{
    while (*members) {
        if (my_strcmp(user, *members) == 0)
            return 1;
        members++;
    }
    return 0;
}

char **user_group(char *user)
{
    FILE *file = fopen("/etc/group", "r");
    char line[256];
    char **user_groups = malloc(256 * sizeof(char *));
    int j = 0;
    group_t group;

    if (!file)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        group = get_group_info(line);
        if (group.members && user_list(user, group.members) == 1) {
            user_groups[j] = my_strdup(group.group);
            j++;
        }
    }
    user_groups[j] = NULL;
    fclose(file);
    return user_groups;
}
