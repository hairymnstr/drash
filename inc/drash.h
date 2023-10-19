#ifndef _DRASH_H
#define _DRASH_H 1

#ifndef DRASH_LINE_BUFFER_LEN
#define DRASH_LINE_BUFFER_LEN 256
#endif

#ifndef DRASH_CAN_EXIT
#define DRASH_CAN_EXIT 0
#endif

#ifndef DRASH_PROMPT
#define DRASH_PROMPT "drsh > "
#endif

typedef struct {
    const char *name;
    int (*func)(int argc, char **argv);
} drash_command_t;

extern drash_command_t application_commands[];
extern size_t application_command_count;

int drash(void);

#endif /* ifndef _DRASH_H */