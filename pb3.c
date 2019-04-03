#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Usage %s n\n", argv[0]);
        exit(1);
    }

    int parentPid=getpid();
    int n;

    sscanf(argv[1], "%d", &n);

    int child_pids[n];
    int count = 0;

    

    for (int i = 0; i < n; ++i) {
        printf("...............................[PID=xxxx_%d_].Forking...!!( ' ')ﾉﾉ⌒○~*.......\n", getpid()-parentPid);
        child_pids[i] = fork();
        if (child_pids[i] == 0) { // a child process
            count = i+1;
            printf("[CHILD][pid=xxxx%d][DEPTH=%d][Will wait for me:_%d_]\n", getpid()-parentPid, count, getppid()-parentPid);
        }
    }

    // both a child and its parent process
    int exit_res = 1;
    int res;
    for (int i = count; i < n; i++) {
        printf("\t\t[PID=xxxx_%d_]......waiting.....", getpid()-parentPid);
        waitpid(child_pids[i], &res, 0);
        exit_res += WEXITSTATUS(res);
    
        printf("\tres=%d\n", WEXITSTATUS(res));
    }
    if (count == 0) {
        printf("Total processes: %d\n", exit_res);
        return 0;
    }
    return exit_res;
}