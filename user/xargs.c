#include "kernel/types.h"

#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

int isspace(char c)
{
    return c == '\n' || c == ' ';
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("WTF %d\n", argc);
        exit(0);
    }

    char *xargv[MAXARG];

    // insert old argv
    memcpy(xargv, &argv[1], (argc - 1) * sizeof(char *));


    char line[256];
    while (strlen(gets(line, 256)) > 0) {
        int xargc = argc - 1;

        // format the xargv

        // argv
        int i = 0;
        int len = strlen(line);
        while (i < len) {
            if (isspace(line[i])) {
                ++i;
                continue;
            }

            xargv[xargc++] = &line[i];

            // add \0 to the next space
            while (i < len && !isspace(line[i]))
                i++;
            line[i++] = '\0';
        }

        xargv[xargc] = 0;

        if (fork() == 0) {
            exec(xargv[0], xargv);
            exit(0);
        } else {
            wait((int *) 0);
        }
    }

    exit(0);
}
