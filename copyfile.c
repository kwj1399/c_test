#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    FILE *fRead,*fWrite;
    char tmp;
    long charcount=0;
    if(argc!=3)
    {
      printf("need two files!\n");
      exit(1);
    }
    else
    {
        if((fRead=fopen(argv[1],"r"))==NULL)
           {
               printf("File1 can not open!\n");
               exit(1);
           }

        else if((fWrite=fopen(argv[2],"w"))==NULL)
            {
               printf("File2 can not open!\n");
               exit(1);
            }
        else
            {
                printf("Copy %s to %s\n",argv[1],argv[2]);
                puts("Copying....");
                while((tmp=getc(fRead))!=EOF)
                {
                    putc(tmp,fWrite);
                    charcount++;
                }

            }
    }
    fclose(fWrite);
    fclose(fRead);
    printf("total char :%ld\n",charcount);
    return 0;

}
