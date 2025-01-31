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

#ifndef MY_H_
    #define MY_H_
node_t *get_password(char *user);
int check_password(node_t *node, char *password);
int verify_password(char *user);
char *extract_username(char *line, int uid);
char *get_username(int uid);
node_t *parse_line(char *line, char *user);
node_t *create_node(char *hashed_pass);
char *get_username(int uid);
int main(int argc, char **argv);
#endif /* !MY_H_ */
