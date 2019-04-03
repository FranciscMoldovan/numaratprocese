#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

    if (argc != 2){
        printf("USAGE: %s <number of iterations in fork bomb>\n", argv[0]);
        exit(-1);
    }

    int fd;
    int depth = 0; /* keep track of number of generations from original */
    int i;
    int childStatus;
    int numIter = 0;

    sscanf(argv[1], "%d", &numIter);
    printf ("YOU CHOSE %d iterations\n", numIter);

    fd = open("fis.txt", O_WRONLY);
    ftruncate(fd, 0);
    
  
    for(i=0; i<numIter; i++) {
        if(fork() == 0) {  /* fork returns 0 in the child */
            int sts = write(fd, &i, 1);  /* write one byte into the pipe */      
            printf("my PID was:%d, [sts=%d], I was in depth %d \n", getpid(), sts, i);
            depth += 1;
        } else 
        {
            wait(&childStatus);
        }
    }

    close(fd);  

    if( depth == 0 ) { /* original process */
      i=0;

      fd = open("fis.txt", O_RDONLY);
      while(read(fd,&depth,1) != 0)
      {
        i += 1;
      }
      printf( "%d total processes spawned\n", i);
    }
    return 0;
}