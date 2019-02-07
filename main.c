#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

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
	int i;

	fscanf(fPointer, "%i", &numOfForks);

	pid_t pidHolder[numOfForks];

	for(i = 0; i < numOfForks; i++){

		if((pidHolder[i] = fork()) == 0){	  
			//open file addto it and close file
			printf("child-pid %d from parent-pid %d\n", getpid(), getppid());
			exit(0);
		}
	}//end for

	for(i = 0; i < numOfForks; i++)
		wait(NULL);

	fclose(fPointer);

	printf("%d\n", pidHolder[0]);
	printf("%d\n", pidHolder[2]);

	return 0;
}//end main
