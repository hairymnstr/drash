#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "drash.h"
#include "drash_builtin_commands.h"

__attribute__((__weak__)) drash_command_t application_commands[] = {};
__attribute__((__weak__)) size_t application_command_count = 0;

int (*drash_find_command(const char *cmd))(int, char **)
{
    // check for a built-in ROM function
    for (size_t i=0;i<drash_builtin_command_count;i++)
    {
        if (strcmp(cmd, drash_builtin_commands[i].name) == 0)
        {
            return drash_builtin_commands[i].func;
        }
    }

    // check for a ROM function from outside the library
    for (size_t i=0;i<application_command_count;i++)
    {
        if(strcmp(cmd, application_commands[i].name) == 0)
        {
            return application_commands[i].func;
        }
    }

    // add searchers for external executables or even scripts here

    return NULL;    // if no command in path return NULL
}

int drash_execute_command(char *linebuffer)
{
    int rv = 0;
    if (strlen(linebuffer) == 0)
    {
        return 0;
    }
    char *save_ptr;
    char **argv = (char **)malloc(sizeof(char *) * 16);
    if (argv == NULL)
    {
        printf("Out of memory!\n");
        return -1;
    }
    argv[0] = strtok_r(linebuffer, " ", &save_ptr);
    int argc = 0;
    if (argv[0])
    {
        do
        {
            argc++;
            if(argc == 15)
            {
                argv[argc] = NULL;
                break;
            }
            argv[argc] = strtok_r(NULL, " ", &save_ptr);
        } while (argv[argc] != NULL);

        int (*func)(int, char **) = drash_find_command(argv[0]);
        if (func)
        {
            rv = func(argc, argv);
        }
    }
    free(argv);
    return rv;
}

int drash(void) {
    bool running = true;
    int idx = 0;
    char last_char = '\0';
    char *line_buffer = (char *)malloc(DRASH_LINE_BUFFER_LEN);
    if (line_buffer == NULL)
    {
        return -1;
    }

    write(STDOUT_FILENO, DRASH_PROMPT, strlen(DRASH_PROMPT));
    while (running)
    {
        char c;
        if (read(STDIN_FILENO, &c, 1) < 1)
        {
            return -1;
        }
        switch (c)
        {
            case '\n':
            {
                if (last_char == '\r')
                {
                    break;
                }
            }
            // if the last character wasn't a \r we got just \n so handle it as an enter key
            // fall through
            case '\r':
            {
                write(STDOUT_FILENO, "\r\n", 2);
                drash_execute_command(line_buffer);
                line_buffer[0] = '\0';
                idx = 0;
                write(STDOUT_FILENO, DRASH_PROMPT, strlen(DRASH_PROMPT));
                break;
            }
            case '\x08':
            case 127:
            {
                if (idx > 0)
                {
                    idx --;
                    line_buffer[idx] = '\0';
                    write(STDOUT_FILENO, "\x08 \x08", 3);
                }
                break;
            }
#if DRASH_CAN_EXIT
            case '\x04':        // Ctrl-D
            {
                running = false;
                break;
            }
#endif
            default:
            {
                if ((c >= ' ') && (c <= '~'))
                {
                    if (idx < (DRASH_LINE_BUFFER_LEN - 1))
                    {
                        line_buffer[idx++] = c;
                        line_buffer[idx] = '\0';
                        write(STDOUT_FILENO, &c, 1);
                    }
                }
            }
        }
        last_char = c;
    }
    free(line_buffer);
    return 0;
}