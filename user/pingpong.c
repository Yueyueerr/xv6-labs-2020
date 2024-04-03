#include "kernel/types.h"
#include "user/user.h"

 int main(int argc,char *argv[]){
    int fds1[2],fds[2];
    char buf[]={'a'};
    int n,pid;
    pipe(fds);
    pipe(fds1);
    //son send fds[1],parent receive in fds[0]
    //parent send fds1[1],son receive in fds1[0]

    pid=fork();
    if(pid==0){//son
        n=getpid();
        close(fds1[1]);
        close(fds[0]);
        write(fds[1],buf,1);
        read(fds1[0],buf,1);
    
        printf("%d: received ping\n",n);
       
        exit(0);
    }
    else{//parent
        n=getpid();
        close(fds[1]);
        close(fds1[0]);
        write(fds1[1],buf,1);
        read(fds[0],buf,1);
       
        printf("%d: received pong\n",n);
        exit(0);
    }
    
 }