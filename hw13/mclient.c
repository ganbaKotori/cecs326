#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct MyBuf{
  long mtype;
  char mtext[10];
  int number;
};

int main () {
  int result;
  int status;

  char obuf[4];

  key_t mykey;
  int msgsz = 10;
  int queueid;
  mykey = ftok("text",'x');
  queueid = msgget(mykey, IPC_CREAT | 0600);

  struct MyBuf buffer;
  buffer.mtype = 1;
  strcpy(buffer.mtext, "Hello");

  int multiplicand;
  int multiplier;
  int product;
  
  for(int i = 0; i < 5; i++){
  //result = mkfifo("fifo.pipe",0600);
  printf("\nEnter multiplicand: ");
  fgets(obuf,4,stdin);
  multiplicand = atoi(obuf);

  //struct MyBuf buffer;
  buffer.mtype = 1;
  buffer.number = multiplicand;
  //strcpy(buffer.mtext, obuf);

  status = msgsnd(queueid, (struct msgbuf*)&buffer,10,0);
  status = msgrcv(queueid, (struct msgbuf *)&buffer,10, 1, 0);
  strcpy(obuf,buffer.mtext);
  printf("%d\n",buffer.number);

  
  //printf("\nEnter multiplier: ");
  //fgets(obuf, 20, stdin);
  //multiplicand = atoi(obuf);

  //printf("\nProduct: %d\n",product);
  }


  return 0;
};
