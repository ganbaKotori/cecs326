#include "sys/wait.h"
#include <stdlib.h> /* Needed for fork */
#include <stdio.h> /* Needed for printf. */
#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */

int sum;
int main (int argc,char* argv[]) {
  int i;
  int result;
  int ch;
  sum = 0;
  printf("sleeping");
  sleep(5);
  result = fork();  /* create a new process */
  for (i=1; i<=10; i++) {
    //ch = getchar();
    if (result == 0){
	ch = getchar();
        printf("%c%d Letter: %c\n",'C',result,ch);
        sleep(1);
	}

    if (result != 0) {
	ch = getchar();
	printf("%c%d %c\n", 'p', result,ch);
	sleep(1);
	}
    sum += i;
    printf("sum is %d\n", sum);
    fflush(stdout);
  }

 if(result != 0 && argc > 1){
	wait3(NULL, 0 , NULL);
	} 
 if (result == 0 && argc < 1){ 
	return 1;
        }
  return 0;
};
