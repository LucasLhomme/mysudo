/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** the main file
*/
#include "lib.h"

int main(int argc, char *argv[])
{
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'h'
        && argv[1][2] == '\0') {
        my_printf("usage: ./my_sudo -h\n");
        my_printf("usage: [-ugEs] [command [args ...]]\n");
        return EXIT_SUCCESS;
    }
    return 0;
}