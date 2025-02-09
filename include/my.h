/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my.h BOOTCAMP
*/
typedef struct node_s {
    char *pwd;
    char *id;
    char *salt;
} node_t;

typedef struct group_s {
    char **members;
    char *group;
} group_t;

typedef struct user_groups_s {
    char *group;
    char **user_groups;
    char **members;
    char *users_in_group;
    int j;
} user_group_t;

#ifndef MY_H_
    #define MY_H_
    #include <crypt.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>
node_t *get_password(char *user);
int check_password(node_t *node, char *password);
int verify_password(char *user);
char *extract_username(char *line, int uid);
char *get_username(int uid);
node_t *parse_line(char *line, char *user);
node_t *create_node(char *hashed_pwd);
int main(int argc, char **argv);
char **user_group(char *user);
char **parse_sudoers(void);
int check_group(char **group, char *user);
int command_exists(char *cmd);
#endif /* !MY_H_ */
