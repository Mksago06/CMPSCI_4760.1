/*
 *Program By : Michael Sago
 *Date : Feb 11 2019
 *CMPSCI_4760
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "stack.h"

int main(int argc, char **argv){

	int option;

	char * input = malloc(32 * sizeof(char) + 1);
	char * output = malloc(32 * sizeof(char) + 1);

	strcpy(input, "input.dat");
	strcpy(output, "output.dat");

	while((option = getopt(argc, argv, "hi:o"))!= -1){

		switch(option){

		case 'h' :
			printf("\t\t---Help Menu---\n");
			printf("\t-h Show Help Menu\n");
			printf("\t-i Specify input file name\n");
			printf("\t-o Specify output file name\n");
			break;

		case 'i' :
			strcpy(input, optarg);
			break;

		case 'o' :
			strcpy(output, optarg);
			break;
			
		case '?' :
			printf("ERROR: Improper arguments");
			return;
		}//end swith
	}//end while
	
	//open input file
	FILE * fPointer = fopen(input, "r");

	//if input file failed to open
	if(input == NULL){
		
		perror("ERROR: Input file failed to open");
	}

	//create pointer variable for output file
	FILE * fp;		
	
	
	int numOfForks;
	int i, j, k;//iterator variables

	//get number of forks 
	fscanf(fPointer, "%i", &numOfForks);

	pid_t pidHolder[numOfForks];//array to hold child processes

	//for loop to fork off children
	for(i = 0; i < numOfForks; i++){

		if((pidHolder[i] = fork()) == 0){
			//child process	  	  
			//open file amend to it and close file

			char readLine[100];
			int stackNums;

			//get how many numbers go into stack 
			fscanf(fPointer, "%i", &stackNums);

			//open output file
			//if not created, create it and amend to it
			fp = fopen(output, "a+");
			
			//initialize stack			
			struct Stack* stack = createStack(stackNums);
			
			//skip a line 
			//read in numbers
			fgetc(fPointer);	
			fgets(readLine, 100, fPointer);

			//strtok() usage "tutorialspoint"
			char s[2] = " ";
			char* token;
			
			//get first token
			token = strtok(readLine, s);

			//walk through other tokens
			//and push to the stack
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
			
			//skip lines 
			fgetc(fPointer);
			fgets(read, 100, fPointer);
			fgetc(fPointer);
			fgets(read, 100, fPointer);
			waitpid(pidHolder[i], &exitStatus, 0);
		}//end else
	}//end for

	fp = fopen(output, "a+");

	fprintf(fp, "All children were: ");

	for(k = 0; k < numOfForks; k++){

		fprintf(fp, "%d ", pidHolder[k]);
	}

	fprintf(fp, "\n");

	fclose(fPointer);
	fclose(fp);
	return 0;
}//end main

