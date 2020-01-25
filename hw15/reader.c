#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/shm.h>

int main(){
	int semid, ch, shareid, returnid;
	key_t mykey;
	union wait waitstatus;
	int* common;
	common[6];

	static struct sembuf OpList[2];
	static struct sembuf ReaderLock = {0,-1,SEM_UNDO};
	static struct sembuf ReaderUnlock = {0,1,SEM_UNDO};
	static struct sembuf WriterLock = {1,-1, SEM_UNDO};
	static struct sembuf WriterUnlock = {1,1,SEM_UNDO};
	
	mykey = ftok("a.out", 'a');
	shareid = shmget(mykey, 3, IPC_CREAT| 0600);

	if((semid = semget(mykey,4,IPC_CREAT| IPC_EXCL | 0600)) != -1){
		semctl(semid,0,SETVAL,1);
		semctl(semid,1,SETVAL,1);
		semctl(semid,2,SETVAL,1);
		semctl(semid,3,SETVAL,0);
		shareid = shmget(mykey,3,IPC_CREAT | 0600);
		common = shmget(shareid,0,0);
		common[0] = 1;
		common[1] = 1;
		common[2] = 1;
	} else {
		semid = semget(mykey,4,0600);
		shareid = shmget(mykey,3,0600);
		common = shmat(shareid,0,0);
	}
	printf("%d\n",semid);

	for(int i=0; i < 5; i++){
		OpList[0] = ReaderLock;
		OpList[1] = WriterLock;
		semop(semid, OpList, 2);
		printf("Byte 1: %d\n",common[0]);
		sleep(1);
		printf("Byte 2: %d\n", common[1]);
		sleep(1);
		printf("Byte 3: %d\n", common[2]);
		sleep(1);
		OpList[0] = ReaderUnlock;
		OpList[1] = WriterUnlock;
		semop(semid, OpList, 2);
		sleep(3);
	}
}
