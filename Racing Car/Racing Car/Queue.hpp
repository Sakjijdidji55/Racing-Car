#ifndef QUEUE_HPP
#define QUEUE_HPP
#define MAX_SIZE 10

typedef struct {
	int front;
	int end;
	int* data;
	int* x;
	int* y;
} Queue;

Queue* initQueue();

int isEmpty(Queue* obj);

void push(Queue* obj, int val,int x,int y);

void pop_front(Queue* obj);

#endif