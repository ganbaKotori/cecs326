#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>

int main(){
        static struct sembuf Wait = {0,-2,SEM_UNDO};
        static struct sembuf Signal = {0,2,SEM_UNDO};

        key_t mykey;

        int semid;

        mykey = ftok("text",'x');

	if ((semid = semget(mykey,1,IPC_CREAT | IPC_EXCL| 0600)) != -1)
	semctl(semid, 0, SETVAL, 5);
	else{
	semid = semget(mykey,1,0600);
	printf("Semaphore id:%d\n", semid);
	}

	for(int i = 0; i < 5; i++){

        semop(semid, &Wait, 1);
        printf("LightWeight Starting\n");
        sleep(4);

        semop(semid, &Signal, 1);
        printf("LightWeight Ending\n");
	sleep(8);
	}

}

