#include <rpc/des_crypt.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <crypt.h>
int main (int argc, char* argv[]) {
  char* key = "mysecretkey";
  int choice = 1;
  int src_fd;
  int dataSize = 16;
  int dest_fd;
  char filebuf[16]; /* a small buffer used to copy the file */
  ssize_t readSize;

  //for(int k=0; k < 64; k++){
	//key[k] = k%2;
//} 
  //setkey(key);

  src_fd = open(argv[1],O_RDONLY);
  dest_fd = open(argv[2],O_CREAT | O_RDWR | O_EXCL, 0777);

  if(src_fd < 0){
    printf("Source file does not exist!\n");
    return 0;
  }
  if(argv[3][0] == 'e'){
	choice = 0;
       
  }

  if(dest_fd < 0){
    printf("Destination file already exists!\n");
    return 0;
  }
  //memset(filebuf,0,64);

  while (( readSize = read(src_fd, filebuf, sizeof(filebuf))) > 0)
  {
    if(choice == 0)
    ecb_crypt(key,filebuf,dataSize,DES_ENCRYPT);
    else ecb_crypt(key,filebuf,dataSize,DES_DECRYPT);
    if(write(dest_fd,filebuf,readSize) <  0)
       return 0;
       //memset(filebuf,0,64);
    // I turn it into a string only because I'm using printf;
    // making a copy using "write" would not need this.
    //filebuf[readSize] = '\0';
    //printf("%s",filebuf);
  }
  close(src_fd);
  close(dest_fd);
  return 0;
}

