#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "stack.h"

int main(int argc, char **argv){
	int option;

	while((option = getopt(argc, argv, "hio"))!= -1){

		switch(option){
		case 'h' :
			printf("Help Menu");
			break;

		case 'i' :
			printf("Input FILE");
			break;

		case 'o' :
			printf("Output FILE");
			break;
			
		default :
			printf("Error");	
		}//end swith
	}//end while
	
	FILE * fPointer = fopen("input.txt", "r");

	int numOfForks;
	int i, j;

	fscanf(fPointer, "%i", &numOfForks);

	pid_t pidHolder[numOfForks];

	for(i = 0; i < numOfForks; i++){
	
	
		if((pidHolder[i] = fork()) == 0){	  
			//open file addto it and close file

			char readLine[100];
			int stackNums;
			fscanf(fPointer, "%i", &stackNums);
						
			struct Stack* stack = createStack(stackNums);
			
			fgetc(fPointer);	
			fgets(readLine, 100, fPointer);

			char s[2] = " ";
			char* token;
			
			token = strtok(readLine, s);

			while(token != NULL){
				
				if(!isFull(stack)){
					
					push(stack, atoi(token));
				}

				token = strtok(NULL, s);
			}//end while
//Pop numbers back off and write to file	
			printf("child-pid %d from parent-pid %d\n", getpid(), getppid());
			exit(0);
		}else{
			//fgets(readLine, 100, fPointer);
			//fgets(readLine, 100, fPointer);
			char read[100];
			int exitStatus;
			waitpid(pidHolder[i], &exitStatus, 0);
			fgetc(fPointer);
			fgets(read, 100, fPointer);
			fgetc(fPointer);
			fgets(read, 100, fPointer);
		}
	}//end for

	for(i = 0; i < numOfForks; i++)
		wait(NULL);

	fclose(fPointer);

	printf("%d\n", pidHolder[0]);
	printf("%d\n", pidHolder[2]);

	return 0;
}//end main

