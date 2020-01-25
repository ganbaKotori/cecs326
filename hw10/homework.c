#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h> 

int main(){
	static struct sembuf Wait = {0,-1,SEM_UNDO};
        static struct sembuf Signal = {0,1,SEM_UNDO};

	key_t mykey;
	int forkID;
	int semid;
	mykey = ftok("text",'x');
	semid = semget(mykey,1,IPC_CREAT | 0600);

	printf("Semaphore id:%d\n", semid);
	semctl(semid,0,SETVAL,1);

	forkID = fork();

	for(int i = 0; i < 10; i++){
	if (forkID == 0){
			semop(semid, &Wait, 1);
			printf("N/S car entering intersection\n");
			sleep(1);
			semop(semid, &Signal, 1);
			printf("N/S car leaving intersection\n");
		}
	else{
			semop(semid, &Wait, 1);
			printf("E/W car entering intersection\n");
			sleep(1);
			semop(semid, &Signal, 1);
			printf("E/W car leaving intersection\n");
		}
	}

}
