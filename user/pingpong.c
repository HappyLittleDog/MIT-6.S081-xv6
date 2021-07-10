#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char* argv[])
{
    int fd[2];
    char buf[16];
    pipe(fd);
    if (fork()==0)
    {
        read(fd[0],buf,1);
        fprintf(1,"%d: received ping\n",getpid());
        write(fd[1],"b",1);
        exit(0);
    }
    write(fd[1],"a",1);
    wait(0);
    read(fd[0],buf,1);
    fprintf(1,"%d: received pong\n",getpid());
    exit(0);
}