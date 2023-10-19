#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include "drash.h"

int extend_cmd(int argc __attribute__((__unused__)), char *argv[] __attribute__((__unused__)))
{
    printf("This is an example command from outside the core library.\n");
    return 0;
}

drash_command_t application_commands[] = {
    {
        .name = "extend",
        .func = extend_cmd,
    },
};
size_t application_command_count = sizeof(application_commands) / sizeof(drash_command_t);

int main(int argc, char *argv[])
{
    struct termios term, term_orig;
    if (tcgetattr(STDIN_FILENO, &term_orig))
    {
        printf("tcgetattr failed: %s\n", strerror(errno));
        exit(-1);
    }

    term = term_orig;

    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &term))
    {
        printf("tcsetattr failed: %s\n", strerror(errno));
        exit(-1);
    }

    drash();

    tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
    exit(0);
}