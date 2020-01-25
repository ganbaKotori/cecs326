#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void catch (int sig)
{
  printf("Got signal %d\n",sig);
  if(SIGALRM == sig){
     printf("Ring Ring");
     fflush(stdout);
     }
}

int main ()
{
  int i;
  struct sigaction psa;
  psa.sa_handler = catch;
  sigaction(SIGINT, &psa, NULL);
  sigaction(SIGALRM, &psa, NULL);
  alarm(6);
  for (i=0;i<20;i++) {
    printf("%d\n",i);
    sleep(1);
  }
  return 0;
}

/* control c prints Got signal 2 */
/* after 6 seconds the program stops (Alarm clock) */
