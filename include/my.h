/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my.h BOOTCAMP
*/
typedef struct node_s {
    char *user;
    char *pwd;
    char *id;
    char *salt;
    struct node_s *next;
} node_t;

typedef struct user_s {
    char *user;
    char *pwd;
    char *id;
    char *salt;
} user_t;

#ifndef MY_H_
    #define MY_H_

int main(int argc, char **argv);
#endif /* !MY_H_ */
