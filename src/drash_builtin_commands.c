#include <stdlib.h>
#include <stdio.h>

#include "drash.h"
#include "drash_builtin_commands.h"

int cmd_dummy(int argc, char **argv)
{
    printf("This is a dummy command\n");
    printf("It was called with %d arguments\n", argc);
    printf("The arguments were:\n");
    for (int i=0;argv[i] != NULL; i++)
    {
        printf("  \"%s\"\n", argv[i]);
    }
    return 0;
}

const drash_command_t drash_builtin_commands[] = {
    {
        .name = "dummy",
        .func = cmd_dummy,
    },
};

const size_t drash_builtin_command_count = sizeof(drash_builtin_commands) / sizeof(drash_command_t);