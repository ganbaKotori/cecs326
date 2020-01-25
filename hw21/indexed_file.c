#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The start of the strings in the file that has been indexed */
int File_Index[64];
int String_Sizes[64];

/* How many strings in the file that has been indexed (-1 means
we haven't indexed yet */
int String_Count = -1;

/*
Fill in the File_Index array with the location of the start of each of
the strings in the file.
Also, Set String_Count to be the number of strings you found.
*/
/*
Caution, to set the string size you will need a variable
that remembers where the string began and do some arithmetic.
*/
void Index_The_File(int fd)
{
  /* get the size of the file */
  int size = (int)lseek(fd, 0, SEEK_END);
  //printf("File Size: %d\n",(int)lseek(fd, 0, SEEK_END));

  /* if the file size is 0, set the string count to be 0 and return */
  if(size ==0)
    return;
  /* Set the first index to be location 0 */
  File_Index[0] = 0;
  /* Set the string count to be 1 */
  String_Count = 1;

  /* Loop, stop at the end of file */
  for(int i = 0; i < size; i++ ){
	char* obuf;
	lseek(fd,i,SEEK_SET);
	read(fd,obuf,1);
	//printf("%s",obuf);

     /* Inner loop, stop at the \0 */
	if(*obuf == '\0' && i != size-1){

     /* if the stopping place is not the last byte of the file
        Set the index location of the next string to be one more
        than the stopping place. Set the size of the string.
        When you set the size of the string, remember to include
        the \0 in the size so we have a printable string.
        Increment the string count.  Increment the file position. */

	File_Index[String_Count] = i+1;
	String_Count += 1;
	}
   }
}

void Get_String(int fd, char* answer_string, int which_string)
{
  /* if which_string is too large (compare against String_Count)
     strcpy "" into answer_string and return */
    if(which_string > String_Count-1){
	strcpy(answer_string,"");
    }
  /* Seek to the starting location of the string in the file.
     Read the string into the answer_string. */
    else if(which_string < String_Count-1){
	lseek(fd, File_Index[which_string], SEEK_SET);
        read(fd, answer_string, File_Index[which_string+1]-File_Index[which_string]);
    }
    else if(which_string == String_Count -1){
        int size = (int)lseek(fd, 0, SEEK_END);
        lseek(fd, File_Index[which_string], SEEK_SET);
        read(fd, answer_string, (size+1) - File_Index[which_string]);
    }
}

/*
The Main program, this is really a tester for the procedures
Index_The_File and Get_String, which you have built.
You shouldn't need to change this unless I've made a mistake.
*/
int main()
{
  int fd;
  char user_input_string[64];
  int user_input_integer;

  char string_from_file[128];

  fd = open("string_file",O_RDONLY);
  Index_The_File(fd);

  while (1)
  {
    printf("Type the index of a string to get or a negative number to exit\n");
    fgets(user_input_string,sizeof(user_input_string)-1,stdin);
    user_input_integer = atoi(user_input_string);

    if (user_input_integer < 0)
    {
       /* exit the program */
      return 0;
    }
    printf("Retrieving the String %d\n",user_input_integer);

    Get_String(fd, string_from_file,user_input_integer);

    printf("String retrieved\n");
    printf("String is: %s\n",string_from_file);
  }
};
