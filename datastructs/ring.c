#include<stdlib.h>
#ifndef RING_H
#define RING_H

/* A ring buffer for multi-threaded programs. A single producer pushes
 * objects into the ring, while a single consumer pops them off for
 * processing. If the ring is full (i.e., the consumer is slower than the
 * producer), then the push operation fails.
*/

#include<stdio.h>

struct ring
{
	int push;
        int pop;
	int size;
	int count;
	
	int *buffer;	
};

/* Create a ring buffer with the specified size. Return the ring or NULL
   if there is not enough memory to create. */
struct ring* ring_create(int size)
{
	if (size <= 0)  return NULL;
	
	struct ring *rb=(struct ring*)malloc(sizeof(struct ring));
	rb->push = 0;
	rb->pop = 0;
	rb->size = size;
	rb->count = 0;
	
	rb->buffer = (int*)malloc(size*sizeof(int));
	
	return rb;
};

/* Add an entry to the ring.
        Return 0 on success, or a sensible error code if ring is full
*/
int ring_push(struct ring *rb, int* data)
{ 
	if(rb->count>=rb->size)
		return -1;
	else
	{
		rb->buffer[rb->push]=*data;
		rb->count=rb->count + 1;
		rb->push=(rb->push+1)%rb->size;
		return 0;
	}
	
}

/* Remove an entry from the ring.
        Return a pointer to the data, or NULL if empty
*/


int* ring_pop(struct ring *rb)
{	
	int *data;
	if(rb->count <= 0)
		return NULL;
	else{	
	data=&rb->buffer[rb->pop];
//	memcpy(data, rb->buffer+rb->pop*sizeof(int), sizeof(int));
	rb->count=rb->count - 1;	
	rb->pop=(rb->pop+1)%rb->size;

	return data;
	}
}

#endif

