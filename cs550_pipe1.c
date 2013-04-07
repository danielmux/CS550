#include "uinclude.h"

int  pd[2], n, i;
char line[256], *s="data from pipe ";

main()
{
   pipe(pd);     // create a pipe
   if (fork()){  // fork a child as READER, parent as WRITER
       printf("parent  %d close pd[0]\n", getpid());
       close(pd[0]);
       while(i++ < 10){  // parent writes to pipe
           printf("parent  %d writing pipe: %s\n", getpid(), s);
           write(pd[1], s, strlen(s));
       }
       printf("parent %d exit\n", getpid());
       exit(0);
   }
   else{         // child as pipe READER
       printf("child %d close pd[1]\n", getpid());
       close(pd[1]);
       while(1){   // child reads from pipe
           printf("child %d reading from pipe\n", getpid());
           if ((n = read(pd[0], line, 256)) == 0)
               exit(0);
           line[n]=0; printf("%s  n=%d\n",line,  n);
       }
   }
}

