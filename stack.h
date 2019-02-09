#include <stdlib.h>

struct Stack{

	int top;
	int capacity;
	int* array;
};

struct Stack* createStack(int);
int isFull(struct Stack*);
int isEmpty(struct Stack*);
void push(struct Stack*, int);
int pop(struct Stack* stack);
