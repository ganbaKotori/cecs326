#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int main (int argc, char* argv[]) {
  int src_fd;
  int dest_fd;
  char filebuf[256]; /* a small buffer used to copy the file */
  ssize_t readSize; 

  src_fd = open(argv[1],O_RDONLY);
  dest_fd = open("/xfer.tmp",O_CREAT | O_RDWR | O_EXCL, 0777);

  if(src_fd < 0){
    printf("Source file does not exist!\n");
    return 0;
  }

  if(dest_fd < 0){
    printf("Destination file already exists!\n");
    return 0;
  }

  while (( readSize = read(src_fd, filebuf, sizeof(filebuf)-1)) > 0)
  {
    if(write(dest_fd,filebuf,readSize) <  0)
       return 0;
    // I turn it into a string only because I'm using printf;
    // making a copy using "write" would not need this.
    filebuf[readSize] = '\0';
    printf("%s",filebuf);
  }
  close(src_fd);
  close(dest_fd);
  return 0;
}

