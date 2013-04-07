#include "uinclude.h"

int  pd[2], n, i;
char line[256], *s="data from pipe ";

main()
{
   pipe(pd);     // create a pipe
   if (fork()){  // fork a child as WRITER, parent as READER
       printf("parent  %d close pd[1]\n", getpid());
       close(pd[1]);
       while(i++ < 10){  // parent read from pipe
           printf("parent  %d reading from pipe\n", getpid());
           if ((n = read(pd[0], line, 256)) == 0)
               exit(0);
           line[n]=0; printf("%s  n=%d\n",line,  n);
       }
       printf("parent %d exit\n", getpid());
       exit(0);
   }
   else{         // child as pipe WRITER
       printf("child %d close pd[0]\n", getpid());
       close(pd[0]);
       while(1){   // child writes to pipe
           printf("child %d writing pipe : %s\n", getpid(), s);
           write(pd[1], s, strlen(s));
       }
   }
}

