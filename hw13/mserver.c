#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

volatile sig_atomic_t stop;

void inthand(int signum) {
        exit(1);
	stop = 1;
}

struct MyBuf{
  long mtype;
  char mtext[10];
  int number;
};


int main () {

  signal(SIGINT,inthand);
  int multiplier;
  int multiplicand;
  int product;
  int result;

 while(!stop){
  int status;

  char obuf[4];

  key_t mykey;
  int msgsz = 10;
  int queueid;
  mykey = ftok("text",'x');
  queueid = msgget(mykey, 0600);

  struct MyBuf buffer;

  status = msgrcv(queueid, (struct msgbuf *)&buffer, 10, 0, 0);
  //strcpy(obuf,buffer.mtext);

  product = buffer.number * 10;
  buffer.number = product;
  //printf("%d",product);
  status = msgsnd(queueid, (struct msgbuf*)&buffer,10,0);

  //product = multiplicand * multiplier;

}
  return 0;
};
