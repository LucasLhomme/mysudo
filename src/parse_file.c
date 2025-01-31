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

node_t *get_hashed_password(char *user)
{
    FILE *file = fopen("/etc/shadow", "r");
    char line[256], *username, *hashed_pass;
    node_t *node;

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
            if (!dollar1) return NULL;
            char *dollar2 = strchr(dollar1 + 1, '$');
            if (!dollar2) return NULL;
            char *dollar3 = strchr(dollar2 + 1, '$');
            if (!dollar3) return NULL;
            node->id = strndup(dollar1 + 1, dollar2 - dollar1 - 1);
            node->salt = strndup(dollar1, dollar3 - dollar1 + 1);
            node->pwd = strdup(hashed_pass);
            printf("id: %s\nsalt: %s\nhash: %s\n", node->id, node->salt, node->pwd);

            return node;
        }
    }
    fclose(file);
    return NULL;
}

int verify_password(char *user)
{
    char *password;
    node_t *node = get_hashed_password(user);
    
    if (!node)
        return -1;
    int attempts = 0;
    while (attempts < 3) {
        printf("[my_sudo] password: ");
        password = getpass("");
        printf("%s\n", password);
        char *hashed_input = crypt(password, node->salt);
        if (hashed_input && strcmp(hashed_input, node->pwd) == 0) {
            printf("hash return :%s\nhash attendu:%s", hashed_input, node->pwd);
            free(node->id);
            free(node->salt);
            free(node->pwd);
            free(node);
            return 0;
        }
        printf("hash return :%s\nhash attendu:%s\n", hashed_input, node->pwd);
        attempts++;
        printf("Incorrect password. Attempts left: %d\n", 3 - attempts);
    }
    free(node->id);
    free(node->salt);
    free(node->pwd);
    free(node);
    
    return 84;
} 