#include "Queue.hpp"
#include<stdlib.h>

Queue* initQueue() {
	Queue* obj = (Queue*)malloc(sizeof(Queue));
	obj->end = 0;
	obj->front = 0;
	obj->data = (int*)malloc(MAX_SIZE * sizeof(int));
	obj->x = (int*)malloc(MAX_SIZE * sizeof(int));
	obj->y = (int*)malloc(MAX_SIZE * sizeof(int));;
	return obj;
}

int isEmpty(Queue* obj) {
	return obj->end == obj->front;
}

void push(Queue* obj, int val,int x,int y) {
	obj->x[obj->end] = x;
	obj->y[obj->end] = y;
	obj->data[(obj->end)++] = val;
	obj->end %= MAX_SIZE;
}

void pop_front(Queue* obj) {
	obj->front++;
	obj->front %= MAX_SIZE;
}
