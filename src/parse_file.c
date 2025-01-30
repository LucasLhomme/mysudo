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

node_t *add_node(node_t *head, user_t *info)
{
    node_t *new_node = malloc(sizeof(node_t));
    node_t *actual = head;

    if (new_node == NULL)
        return NULL;
    new_node->user = strdup(info->user);
    new_node->pwd = strdup(info->pwd);
    new_node->id = strdup(info->id);
    new_node->salt = strdup(info->salt);
    new_node->next = NULL;
    if (head == NULL)
        return new_node;
    while (actual->next != NULL)
        actual = actual->next;
    actual->next = new_node;
    return head;
}

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

char *get_username(void)
{
    uid_t uid = getuid();
    uid_t file_uid = malloc(sizeof(uid_t));
    FILE *file = fopen("/etc/passwd", "r");
    char line[256];
    char *username = NULL;
    char *user = NULL;

    if (file == NULL)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        user = strtok(line, ":");
        strtok(NULL, ":");
        file_uid = (uid_t)atoi(strtok(NULL, ":"));
        if (file_uid == uid) {
            username = strdup(user);
            break;
        }
    }
    fclose(file);
    return username;
}
