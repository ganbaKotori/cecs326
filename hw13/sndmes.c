#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main () {
  int myqueue;
  key_t mykey;
  int status;

  int msgsz = 10;
  struct Mybuf {
    long mtype;
    char mtext[msgsz];
  };

  for(int i = 0; i < 5; i++){
  	struct Mybuf buf;
  	char obuf[4];

  	printf("\nEnter multiplicand: ");
  	fgets(obuf,20,stdin);
  
  	mykey = ftok( ".cshrc" , 'a' );
  	myqueue = msgget(mykey, IPC_CREAT | 0600 );

  	if ( -1 == myqueue) {
  	  printf("error in msgget");
  	  return 1;
  	}

  	/* no special instructions */
  	buf.mtype = 1;
  	strcpy( buf.mtext , obuf) ;

  	/* no flags */
  	status = msgsnd(myqueue, (struct msgbuf *)&buf, msgsz, 0);

  	printf("\nEnter multiplier: ");
  	fgets(obuf,20,stdin);
  	strcpy( buf.mtext , obuf) ;
	
	status = msgsnd(myqueue, (struct msgbuf *)&buf, msgsz, 0);

  	status = msgrcv(myqueue, (struct msgbuf *)&buf, msgsz, 0, 0);

  	printf("\nProduct: %s\n", buf.mtext);
  	if ( -1 == status) {
    	printf("error in msgsnd %s \n", strerror(errno) );
    	return 1;
  	}
 }
}
