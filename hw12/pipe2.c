#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main() {
  int toParent[2], toChild[2];
  char obuf[20], ibuf[20], eval;
  pipe(toParent); pipe(toChild);
  strcpy(obuf,"Hello\n");
  if (fork()==0) {
    close(toParent[0]); /* child */
    close(toChild[1]);
    write(toParent[1],obuf,20);
    read(toChild[0],ibuf,20);
  } else {
    close(toChild[0]); /* parent */
    close(toParent[1]);
    write(toChild[1],obuf,20);
    read(toParent[0],ibuf,20);
  }
  puts(ibuf);
  return 0;
}

