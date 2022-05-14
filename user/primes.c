#include "kernel/types.h"

#include "kernel/stat.h"
#include "user/user.h"

#define MAX 35

void pipeline(int upper_pipe)
{
    int b;
    if (read(upper_pipe, &b, sizeof(b)) <= 0) {
        exit(0);
    }
    printf("prime %d\n", b);


    int p[2];
    pipe(p);

    int n;
    while (read(upper_pipe, &n, 4) > 0) {
        if (n % b != 0)
            write(p[1], &n, sizeof(n));
    }
    close(p[1]);

    if (fork() == 0) {
        // child
        pipeline(p[0]);
    } else {
        // parent
        wait((int *) 0);
    }

    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc != 1)
        exit(0);


    int p[2];
    pipe(p);

    for (int i = 2; i <= MAX; ++i) 
        write(p[1], &i, sizeof(i));
    close(p[1]);

    if (fork() == 0) {
        // child
        pipeline(p[0]);
    } else {
        // parent
        wait((int *) 0);
    }


    exit(0);
}
