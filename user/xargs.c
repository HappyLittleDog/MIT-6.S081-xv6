#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char* argv[])
{
    char buf[512];
    char* tparg[100];
    int pos=0;
    for (;pos<argc-1;pos++)
    {
        char* tp=malloc(strlen(argv[pos+1])+1);
        strcpy(tp,argv[pos+1]);
        tparg[pos]=tp;
    }
    int bp=0;
    while (read(0,buf+bp,1)>0)
    {
        if (buf[bp]=='\n')
        {
            buf[bp]='\0';
            char* tp=malloc(bp+1);
            strcpy(tp,buf);
            tparg[pos]=tp;
            pos++;
            bp=0;
        }
        else
        {
            bp++;
        }
    }
    tparg[pos]='\0';
    // for (int i=0;i<pos;i++)
    //     fprintf(1,"%s\n",tparg[i]);
    exec(argv[1],tparg);
    exit(0);
}