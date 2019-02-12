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
	FILE * fp;			
	
	int numOfForks;
	int i, j, k;

	fscanf(fPointer, "%i", &numOfForks);

	pid_t pidHolder[numOfForks];

	for(i = 0; i < numOfForks; i++){
	
	
		if((pidHolder[i] = fork()) == 0){
			//child process	  	  
			//open file amend to it and close file

			char readLine[100];
			int stackNums;
			fscanf(fPointer, "%i", &stackNums);
			fp = fopen("output.txt", "a+");
			//FILE * fp = fopen("output.txt", "a+");			
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
			
			//POP numbers and write to file in reverse order	
			fprintf(fp, "%d: ", getpid());

			for (j = 1; j <= stackNums; j++){
				
				fprintf(fp, "%i ", pop(stack));
			}

			fprintf(fp, "\n");
			fclose(fp);
			exit(0);
		}else{
			
			char read[100];
			int exitStatus;

			fgetc(fPointer);
			fgets(read, 100, fPointer);
			fgetc(fPointer);
			fgets(read, 100, fPointer);
			waitpid(pidHolder[i], &exitStatus, 0);
		}
	}//end for

	fp = fopen("output.txt", "a+");

	fprintf(fp, "All children were: ");

	for(k = 0; k < numOfForks; k++){

		fprintf(fp, "%d ", pidHolder[k]);
	}

	fprintf(fp, "\n");

	fclose(fPointer);
	fclose(fp);
	return 0;
}//end main

