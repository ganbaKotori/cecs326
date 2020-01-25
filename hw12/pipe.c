
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int toParent[2], toChild[2];

	char obuf[4], ibuf[4];

	pipe(toParent); pipe(toChild);

	int multiplier;
	int multiplicand;
	int product = 0;
	int result;
	result  = fork();

	if(result==0){
		close(toChild[0]); /*child*/
                close(toParent[1]);

	} else if(result>0){
		close(toParent[0]); /* parent */
                close(toChild[1]);
	}

	for(int i =0; i < 5; i++){
	if(result==0){
                read(toParent[0],&multiplier, 4);
                read(toParent[0],&multiplicand, 4);

                product = multiplier * multiplicand;
                write(toChild[1], &product, 4);
		
	} else if(result > 0){
			printf("Enter first number: \n");
                        fgets(obuf,20,stdin);
                        multiplier = atoi(obuf);
                        write(toParent[1], &multiplier, 4);
			printf("Enter second number: \n");
                        fgets(obuf,20,stdin);
                        multiplicand = atoi(obuf);
                        write(toParent[1], &multiplicand, 4);

                        read(toChild[0], &product, 4);
                        printf("Results: %d\n",product);

	}
	}
	return 0;
}
