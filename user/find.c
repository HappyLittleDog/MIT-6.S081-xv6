#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char* path, char* file)
{
    char buf[512];
    int fd;
    struct dirent de;
    struct stat st;
    if((fd = open(path, 0)) < 0)
    {
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0)
    {
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }
    strcpy(buf,path);
    int n=strlen(path);
    buf[n]='/';
    n++;
    while(read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if(de.inum == 0)
            continue;
        int fd1;
        struct stat st1;
        strcpy(buf+n,de.name);
        if((fd1 = open(buf, 0)) < 0)
        {
            fprintf(2, "ls: cannot open %s\n", buf);
            continue;
        }
        if(fstat(fd1, &st1) < 0)
        {
            fprintf(2, "ls: cannot stat %s\n", buf);
            close(fd1);
            return;
        }
        switch(st1.type)
        {
            case T_FILE:
                if (strcmp(de.name,file)==0)
                    fprintf(1,"%s\n",buf);
                break;
            case T_DIR:
                if (strcmp(de.name,".")!=0 && strcmp(de.name,"..")!=0)
                    find(buf,file);
                break;
        }
        close(fd1);
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(1,"usage: find <dir> <name>\n");
        exit(0);
    }
    find(argv[1],argv[2]);
    exit(0);
}
