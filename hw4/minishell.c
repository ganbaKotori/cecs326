/*
   The parser piece for the minishell assignment
   Replace the part that prints the parsed command
   with you code that does the fork, exec, wait.
*/
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
  char line[40];
  char *nargs[10];
  char *space = " ";
  char *where;
  int result;
  while(1)
  {
    int i = 0;
    printf("Your command please: ");
    fgets(line,sizeof(line),stdin);
    line[strlen(line)-1] = '\0';
    where = strtok(line,space);
    nargs[i++] = where;
    while (where != NULL)
    {
      where = strtok(NULL,space);
      nargs[i++] = where;
    }
    

    int child;
    child = fork();

    if (child == 0){
	execvp(nargs[0],nargs);
	}
    if (child != 0){
	wait3(NULL,0,NULL);
	}
  }
};
