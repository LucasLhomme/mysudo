/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** parse file
*/

#include "lib.h"
#include "my.h"

node_t *create_node(char *hashed_pwd)
{
    node_t *node = malloc(sizeof(node_t));
    char *dollar1 = NULL;
    char *dollar2 = NULL;
    char *dollar3 = NULL;

    if (!node)
        return NULL;
    dollar1 = strchr(hashed_pwd, '$');
    dollar2 = strchr(dollar1 + 1, '$');
    dollar3 = strchr(dollar2 + 1, '$');
    if (!dollar1 || !dollar2 || !dollar3)
        return NULL;
    node->id = strndup(dollar1 + 1, dollar2 - dollar1 - 1);
    node->salt = strndup(dollar1, dollar3 - dollar1 + 1);
    node->pwd = strdup(hashed_pwd);
    return node;
}

node_t *parse_line(char *line, char *user)
{
    char *username = strtok(line, ":");
    char *hashed_pwd = NULL;

    if (username && strcmp(username, user) == 0) {
        hashed_pwd = strtok(NULL, ":");
        if (!hashed_pwd || hashed_pwd[0] == '\0' || hashed_pwd[0] == '!')
            return NULL;
        return create_node(hashed_pwd);
    }
    return NULL;
}

node_t *get_password(char *user)
{
    FILE *file = fopen("/etc/shadow", "r");
    char line[256];
    node_t *node = NULL;

    if (!file)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        node = parse_line(line, user);
        if (node)
            break;
    }
    fclose(file);
    return node;
}

static char *get_input(void)
{
    my_printf("[my_sudo] password: ");
    return getpass("");
}

int check_password(node_t *node, char *password)
{
    char *hashed_input = crypt(password, node->pwd);

    if (hashed_input && strcmp(hashed_input, node->pwd) == 0) {
        return 1;
    }
    return 0;
}

static int free_node(node_t *node)
{
    free(node->id);
    free(node->salt);
    free(node->pwd);
    free(node);
    return 0;
}

int verify_password(char *user)
{
    node_t *node = get_password(user);
    char *password = NULL;
    int attempts = 0;

    if (!node)
        return -1;
    attempts = 0;
    while (attempts < 3) {
        password = get_input();
        if (check_password(node, password)) {
            free_node(node);
            return 0;
        }
        attempts++;
        my_printf("Incorrect password. Attempts left: %d\n", 3 - attempts);
    }
    free_node(node);
    return 84;
}
