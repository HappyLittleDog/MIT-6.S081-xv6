#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
// #include <csapp.h>

void F(int r,int w)
{
    if (fork()==0)
    {
        close(0);
        dup(r);
        close(r);
        close(w);
        char st[1];
        if (read(0,st,1)==0)
            exit(0);
        fprintf(1,"prime %d\n",(int)st[0]);
        int fd[2];
        pipe(fd);
        char cur[1];
        while (read(0,cur,1)>0)
        {
            if (((int)cur[0])%((int)st[0])!=0)
                write(fd[1],cur,1);
        }
        F(fd[0],fd[1]);
    }
    else
    {
        close(r);
        close(w);
        wait(0);
    }
}
int main()
{
    int fd[2];
    pipe(fd);
    for (int i=2;i<=35;i++)
    {
        char s[1];
        s[0]=i;
        write(fd[1],s,1);
    }
    F(fd[0],fd[1]);
    exit(0);
}