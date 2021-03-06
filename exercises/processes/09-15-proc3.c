#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*Aquí solo hay un padre, con una extensión en amplitud*/

void child_process(long ps, char* program){
    long cs;
    sleep(2);
    cs = time(0);
    printf("%s: PID = %i\tPPID = %i\ttime = %li\n", program, getpid(), getppid(), (cs - ps));
    exit(0);
}

int main(int argc, char* argv[]){
    int pid, i, childs;
    long ps;
    
    if(argc != 2){
        fprintf(stderr, "usage: %s num:child\n", argv[0]);
        return -1;
    }
    childs = atoi(argv[1]);
    if (childs <= 0){
        fprintf(stderr, "%s: the number must be a positive greater than 0\n", argv[0]);
        return -1;
    }
    
    ps = time(0);
    for(i = 0; i < childs; i++){
        if( (pid = fork()) < 0 ){
            perror(argv[0]);
            exit(-1);
            //es igual que return(-1) EN ESTE CASO
        } else if(pid == 0){
            child_process(ps, argv[0]);
        }/* else{
            wait(NULL);
        }*/
    }
    while (i > 0){
        pid = wait(NULL);
        printf("\t PID = %i has ended\n", pid);
        i--;
    }
    return 0;
}