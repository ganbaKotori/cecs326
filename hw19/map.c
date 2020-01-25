#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
int main (){
	int location;
	char letter;
	char obuf[4];
	int fd;
	char *filePtr;
	fd = open("mmap.txt", O_RDWR);
	filePtr = mmap(0,100,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("\nEnter location: ");
  	fgets(obuf,20,stdin);
  	location = atoi(obuf);
	printf("\nEnter letter: ");
	fgets(obuf,20,stdin);
        //loca = atoi(obuf);
	filePtr[location] = *obuf;
	munmap(filePtr,20);
	close(fd);
}
