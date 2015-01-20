#include <stdio.h>
#include <stdlib.h>
#include "ring.c"

int main()
{
    struct ring* rb = ring_create(16);

    int data[20];
    int *popdata;
    int i;

    for( i = 0; i<20 ; i++)
    {
	data[i]= i;
	int err=ring_push(rb, &data[i]);
	if(err){
	    printf("push %d fail\n",i);
	}
	else{
	    printf("push data %d = %d\n",i,data[i]);
	}
    }


    for(i = 0; i<20 ; i++)
    {
	popdata=ring_pop(rb);
	if(popdata==NULL){
	    printf("pop %d fail\n",i);
	}
	else{
	    printf("pop data %d = %d\n",i, *popdata);
	}
    }
    return 0;

}
