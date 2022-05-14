#include "kernel/types.h"

#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 1)
        exit(0);


    int p[2];
    pipe(p);

    if (fork() == 0) {
        // child
        char *a;
        read(p[0], &a, 1);

        printf("%d: received ping\n", getpid());

        char b = 'a';
        write(p[1], &b, 1);

        close(p[0]);
        close(p[1]);

    } else {
        // parent
        char b = 'a';
        write(p[1], &b, 1);
        char *a;
        read(p[0], &a, 1);

        printf("%d: received pong\n", getpid());

        close(p[0]);
        close(p[1]);
    }


    exit(0);
}
