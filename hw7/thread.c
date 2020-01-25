#include <sys/wait.h>
#include <stdlib.h> /* Needed for fork */
#include <stdio.h> /* Needed for printf. */
#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
#include <pthread.h>

int sum;
int results;
int ch;
int i;
void *ChildThread(){
    int i;
  for (i=1; i<=10; i++) {
    printf("%c%d %c ",'C',results,ch);
    //sleep(2);
    sum += 1;
    printf("sum is %d\n", sum);
    fflush(stdout);
  }
}

int main (int argc,char* argv[]) {
  sum = 0;
  int i;
  printf("sleeping\n");
  sleep(5);
    pthread_t th;
  pthread_attr_t ta;
  pthread_create(&th, NULL, ChildThread, NULL);
  pthread_attr_setdetachstate(&ta, PTHREAD_CREATE_DETACHED);



  for(i =1; i <= 10; i++){
    printf("%c%d ", 'P',results);
    printf("%c",ch);
    //sleep(2);
    sum +=1;
    printf("Sum is %d\n",sum);
    fflush(stdout);
}

if(argc > 1 && results !=0){
  wait3(NULL,0, NULL);
}
if(argc < 1 || results == 0){
 return 1;
}

  return 0;
};
