#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "drash.h"
#include "drash_builtin_commands.h"

#define OPTPARSE_IMPLEMENTATION
#define OPTPARSE_API static
#include "optparse.h"

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

const char * const __cmd_with_options_help = "NAME:\n" \
"  %s - example with option parser\n" \
"SYNOPSIS:\n" \
"  %s [OPTIONS] [ARGS]\n" \
"DESCRIPTION:\n" \
"  An example command with options.  Use the options\n" \
"  to see how they work.\n" \
"  -h, --help\n" \
"    Print this help and exit\n" \
"  -v, --verbose\n" \
"    Print the optional arguments out.\n";

int cmd_with_options(int argc, char **argv)
{
    bool verbose = false;
    int number = 0;

    struct optparse_long longopts[] = {
        {"verbose", 'v', OPTPARSE_NONE},
        {"help", 'h', OPTPARSE_NONE},
        {0}
    };

    char *arg;
    int option;
    struct optparse options;

    optparse_init(&options, argv);
    while((option = optparse_long(&options, longopts, NULL)) != -1)
    {
        switch (option)
        {
            case 'v':
                verbose = true;
                break;
            case 'h':
                printf(__cmd_with_options_help, argv[0], argv[0]);
                return 0;
            case '?':
                fprintf(stderr, "%s: %s\n", argv[0], options.errmsg);
                return -1;
        }
    }

    if (verbose)
    {
        while ((arg = optparse_arg(&options)))
        {
            printf("%s\n", arg);
        }
    }
    return 0;
}

const drash_command_t drash_builtin_commands[] = {
    {
        .name = "dummy",
        .func = cmd_dummy,
    },
    {
        .name = "optparse",
        .func = cmd_with_options,
    }
};

const size_t drash_builtin_command_count = sizeof(drash_builtin_commands) / sizeof(drash_command_t);