#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

volatile sig_atomic_t stop;

void inthand(int signum) {
        exit(1);
        stop = 1;
}

int main () {
  int myqueue;
  key_t mykey;
  int status;
  int msgsz = 10;
  struct Mybuf {
    long mtype;
    char mtext[msgsz];
  };
  struct Mybuf buf;
  int multiplicand;
  int multiplier;
  int product;
  char obuf[4];

  mykey = ftok( ".cshrc" , 'a' );

  myqueue = msgget(mykey, IPC_CREAT | 0600 );

  if ( -1 == myqueue) {
    printf("error in msgget");
    return 1;
  }
  while(!stop){
	  /* no special instructions, no flags */
	  status = msgrcv(myqueue, (struct msgbuf *)&buf, msgsz, 0, 0);
	  multiplicand = atoi(buf.mtext);
	
	  if ( -1 == status) {
	    printf("error in msgrcv");
	    return 1;
	  }
	
	  status = msgrcv(myqueue, (struct msgbuf *)&buf, msgsz, 0, 0);
	
	  multiplier = atoi(buf.mtext);
	  product = multiplier * multiplicand;
	  snprintf(buf.mtext,10,"%d",product);
	
	  status = msgsnd(myqueue, (struct msgbuf *)&buf, msgsz, 0);

  	}	

}
