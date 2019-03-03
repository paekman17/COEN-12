/*
Ethan Paek
Lab #5
Wednesday Sessions
This is a program that utilizes a priority queue and has a dynamic array (limit of array can be altered) to simulate a min heap
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

//algorithms to determine the parent and left and right children for a given node
static int parent(int i);
static int left(int i);
static int right(int i);

struct pqueue{
  int count;//number of entries in the array
  int length;//length of allocated array
  void** data;//allocated array of entries
  int (*compare)();//comparison function
};

PQ *createQueue(int (*compare)()){//create the priority queue, O(1)
  PQ *pq = malloc(sizeof(PQ));
  assert(pq != NULL);
  pq->compare = compare;
  pq->count = 0;//nothing in the array yet
  pq->length = 10;//set the starting array size to 10
  pq->data = malloc(sizeof(void*)*10);
  assert(pq->data != NULL);
  return pq;
}

void destroyQueue(PQ *pq){//destroy the priority queue, O(n)
  assert(pq != NULL);
  for(int i = 0; i < pq->count; i++){
    free(pq->data[i]);//free each individual void double pointer
  }
  free(pq->data);//free the void pointer
  free(pq);//free the priority queue
  return;
}

int numEntries(PQ *pq){//return the number of integers currently in the priority queue, O(1)
  assert(pq != NULL);
  return pq->count;//return the number of items that are present in the priority queue
}

void addEntry(PQ *pq, void *entry){//insert into the priority queue, O(logn)
  assert(pq != NULL);
  if(pq->count == pq->length){
    pq->length *= 2;
    pq->data = realloc(pq->data, sizeof(void*)*pq->length);//double the array size by allocating into a new array with double pq->length
  }
  pq->data[pq->count] = entry;
  int index = pq->count;//position of the new node
  while(pq->count != 0 && (*pq->compare)(pq->data[parent(index)], pq->data[index]) > 0){//swap the child with the parent if the child is smaller than the parent
    void* swapData = pq->data[index];//remember the child's data
    pq->data[index] = pq->data[parent(index)];
    pq->data[parent(index)] = swapData;
    index = parent(index);//keep heaping up until the heap is in order
  }
  pq->count++;//increase the count by one if you insert into the priority queue
  return;
}

void *removeEntry(PQ *pq){//remove from the priority queue, O(logn)
    assert(pq != NULL);
    void* returnData = pq->data[0];
    pq->data[0] = pq->data[pq->count - 1];//swap the root with the last item in the heap
    int index = 0;
    while(left(index) <= pq->count - 1){//keep heaping down until there is no longer a left child
      int smallerChildIndex = left(index);//record the index of the left child
      if(right(index) <= pq->count - 1){//check to make sure that the right child exists
	if((*pq->compare)(pq->data[right(index)], pq->data[left(index)]) < 0){//if the right child is smaller than the left child, use the index of the right child
	  smallerChildIndex = right(index);
	}
      }
      if((*pq->compare)(pq->data[index], pq->data[smallerChildIndex]) < 0){//if the parent is already smaller than its children, don't do anything
	break;
      }
      else{//swap if this is not the case
	void* swapData = pq->data[index];
	pq->data[index] = pq->data[smallerChildIndex];
	pq->data[smallerChildIndex] = swapData;
      }
      index = smallerChildIndex; //check it again with the child
    }
    pq->count--;//decrease the count by one if you remove from the priority queue
    return returnData;
}

static int parent(int i){
  return (i-1)/2;
}

static int left(int i){
  return (i*2)+1;
}

static int right(int i){
  return (i*2)+2;
}
