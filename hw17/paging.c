

/* paging.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
/* Write a value to memory */
void wr_mem(int Location, int Value);

/* Read a value from memory. */
int rd_mem(int Location);

/* These declarations are global so your procedures can use them */

/* File descriptor for the page file */
int pageFile;

/* Main memory, also called RAM */
int memory[5];

/* The page table, we have only one for this assignment.*/
int pagetable[8];

/*
 Put any globals you need to share between the two procdeures here
 You need the various arrays to remember if a page is in memory,
 and to remember if it was reference and to track what is in a frame.
 You also need to remember where you are in your memory scan.
 You put them here so you can initialize them in the main program
 (once) and use them in both your procedures.
*/
  int inMemory[8]; //1=in memory  0=on disk
  int referenceBit[8];//1=recently used  0=candidate for replacement
  int pageframe[8];
  int SpaceInMem;
  int clearLocation;



int main()
{
  int loopcount;
  /* set up the page file */
  pageFile = open("pagefile.bin",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR | S_IWUSR);
  /* 8 bytes of 0 */
  for (loopcount = 0 ; loopcount < 8 ; loopcount++)
  { 
    write(pageFile,"\0",1); /* cheap way to have an array with a 0 */
    //pageInFrame[loopcount] = -1;
    inMemory[loopcount] =-1;
  } 
//  wr_mem(3,3);
//  int test = rd_mem(3);
//  printf("%d",test);

  /* YOU need to initialize your globals here. */
  //inMemory[8]; //1=in memory  0=on disk
  //referenceBit[8];
  //pageInFrame[8];
    SpaceInMem = 5;


  /*
    YOU DO NOT CHANGE the rest of the main program, this is the part
    that tests to see if you've implemented paging correctly.
  */ 
    
  /* initialize all pages to contain a value */
  for (loopcount = 0 ; loopcount < 8 ; loopcount++)
  {
    /* mem[loopcount] = loopcount; */
    wr_mem(loopcount, loopcount);
  };
  wr_mem(4, 5 + 6 ); /* mem[4] = mem[2] + mem[4] */
  //wr_mem(6, rd_mem(2) + rd_mem(7) ); /* mem[6] = mem[2] + mem[7] */
  //wr_mem(1, rd_mem(1) + rd_mem(3) ); /* mem[1] = mem[1] + mem[3] */
  //wr_mem(5, rd_mem(3) + rd_mem(7) ); /* mem[5] = mem[3] + mem[7] */


  /* cause some more paging */
  //wr_mem(4, rd_mem(2) + rd_mem(4) ); /* mem[4] = mem[2] + mem[4] */
  //wr_mem(6, rd_mem(2) + rd_mem(7) ); /* mem[6] = mem[2] + mem[7] */
  //wr_mem(1, rd_mem(1) + rd_mem(3) ); /* mem[1] = mem[1] + mem[3] */
  //wr_mem(5, rd_mem(3) + rd_mem(7) ); /* mem[5] = mem[3] + mem[7] */

  for (loopcount = 0 ; loopcount < 5 ; loopcount++)
  {
	printf("%d\n",memory[loopcount]);
  };

  printf("\n\n");

  for (loopcount = 0 ; loopcount < 8 ; loopcount++)
  {
	char number;
	lseek(pageFile,loopcount-1,SEEK_SET);
  	read(pageFile,&number,1);
        printf("%d\n",number);
  };

  printf("\n\nIn Memory?\n");

  for (loopcount = 0 ; loopcount < 8 ; loopcount++)
  {
        printf("%d\n",inMemory[loopcount]);
  };

  printf("\n\nPagetable\n");

  for (loopcount = 0 ; loopcount < 8 ; loopcount++)
  {
        printf("%d\n",pagetable[loopcount]);
  };





  /* we are done the test */
  close(pageFile);
  return 0;
};

/* YOU need to implement wr_mem here. */

/* YOU need to implement rd_mem here. */
 /* Write a value to memory */
void wr_mem(int Location, int Value){

  if(Location < 5)
	{
	memory[Location] = Value;
	inMemory[Location] = 1;
	//--
	pagetable[Location] = memory[Location];
	}

  else {
	int moveValue = memory[0];
	printf("move value: %d\n",moveValue);
	lseek(pageFile,moveValue-1,SEEK_SET);
        write(pageFile,&moveValue,1);
	inMemory[moveValue] = 0;

	pagetable[moveValue] = moveValue;
 
 	for (int k = 0; k < 4; k++){
		printf("array: %d\n", memory[k]);
		printf("array next: %d\n", memory[k+1]);
    		memory[k]=memory[k+1];
	}

	for (int k = 0; k < 4; k++){
                pagetable[k] = memory[k];
        }
	
	memory[4] = Value;
	pagetable[4] = memory[4];
	inMemory[Value] = 1;

	}
  char ch;


}

/* Read a value from memory. */
int rd_mem(int Location){
  int ch;
  lseek(pageFile,Location-1,SEEK_SET);
  read(pageFile,&ch,1);
  return ch;

}

