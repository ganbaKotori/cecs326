#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
volatile sig_atomic_t stop;

void inthand(int signum) {
        exit(1);
	stop = 1;
}


int main () {
  
  int fd;
  int fd2;
  signal(SIGINT,inthand);
  int multiplier;
  int multiplicand;
  int product;
  int result;

 while(!stop){
  result = mkfifo("fifo2.pipe",0600);

  char obuf[4];

  fd = open("fifo.pipe",O_RDONLY);

  read(fd,&multiplier,4);
  printf("%d\n",multiplier);
  close(fd);

  fd = open("fifo.pipe",O_RDONLY);
  
  read(fd, &multiplicand,4);
  printf("%d\n", multiplicand);
  close(fd);

  product = multiplicand * multiplier;
  fd2 = open("fifo2.pipe",O_WRONLY);
  write(fd2, &product, 4);
  close(fd2);

}
  return 0;
};
