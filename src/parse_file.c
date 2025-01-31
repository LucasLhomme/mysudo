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

static node_t *get_hashed_password(const char *user)
{
    FILE *file = fopen("/etc/shadow", "r");
    char line[256];
    char *username = NULL;
    char *hashed_pass = NULL;
    node_t *node = NULL;

    if (!file)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        username = strtok(line, ":");
        if (username && strcmp(username, user) == 0) {
            hashed_pass = strtok(NULL, ":");
            fclose(file);
            if (!hashed_pass || hashed_pass[0] == '\0' || hashed_pass[0] == '!')
                return NULL;
            node = malloc(sizeof(node_t));
            if (!node)
                return NULL;
            char *dollar1 = strchr(hashed_pass, '$');
            char *dollar2 = dollar1 ? strchr(dollar1 + 1, '$') : NULL;
            char *dollar3 = dollar2 ? strchr(dollar2 + 1, '$') : NULL;
            if (!dollar1 || !dollar2 || !dollar3)
                return NULL;
            node->id = strndup(dollar1 + 1, dollar2 - dollar1 - 1);
            node->salt = strndup(dollar1, dollar3 - dollar1 + 1);
            node->pwd = strdup(hashed_pass);
            return node;
            printf("\nid:%s\nsalt:%s\nhash:%s\n", node->id, node->pwd, node->salt);
        }
    }
    fclose(file);
    return NULL;
}

static void free_node(node_t *node)
{
    if (!node)
        return;
    free(node->id);
    free(node->salt);
    free(node->pwd);
    free(node);
}

int verify_password(const char *user)
{
    char *password = NULL;
    node_t *node = get_hashed_password(user);
    int attempts = 0;

    if (!node)
        return -1;
    while (attempts < 3) {
        printf("[my_sudo] password: ");
        password = getpass("");
        if (!password)
            break;
        printf("\nmdp:%s", password);
        if (strcmp(crypt(password, node->salt), node->pwd) == 0) {
            free_node(node);
            return 0;
        }
        attempts++;
        printf("Incorrect password. Attempts left: %d\n", 3 - attempts);
    }
    free_node(node);
    return -1;
}