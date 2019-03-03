/*Ethan Paek
Lab 4
February 14th, 2018
This is a program of a doubly circular linked list that can implemented with a stack and queue
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

typedef struct node{
  void *data; //data that's stored within each node
  struct node *next;
  struct node *prev;
}NODE;

typedef struct list{
  int count; //keeps track of number of items in list
  NODE* head; //dummy head node
  int (*compare)(); //compare function provided by interface
}LIST;

LIST *createList(int (*compare)()){
  LIST *pList = malloc(sizeof(LIST));
  assert(pList != NULL);
  pList->count = 0;//list begins with nothing in
  pList->head = malloc(sizeof(NODE));//allocate memory for the head
  assert(pList->head != NULL);
  pList->compare = compare;
  pList->head->prev = pList->head;//set the head pointers to itself
  pList->head->next = pList->head;
  return pList;
}

void destroyList(LIST *lp){
  assert(lp != NULL);
  NODE *pDel;
  NODE *pPrev = lp->head->prev;
  do{//frees all nodes by starting with the tail
    pDel = pPrev;
    pPrev = pDel->prev;
    free(pDel);
  } while(pDel!=lp->head);
  free(lp);
}

int numItems(LIST *lp){//return the amount of items in the list
  assert(lp != NULL);
  return lp->count;
}

void addFirst(LIST *lp, void *item){//add an item to the beginning of the list
  assert(lp != NULL);
  NODE* addNode = malloc(sizeof(NODE));
  assert(addNode != NULL);
  addNode->data = item; 
  lp->head->next->prev = addNode;
  addNode->next = lp->head->next; //set the pointers for the new node
  addNode->prev = lp->head;
  lp->head->next = addNode;
  lp->count++; //add one to count since you added a new node
  return;
}

void addLast(LIST *lp, void *item){
  assert(lp != NULL);
  NODE* addNode = malloc(sizeof(NODE));
  assert(addNode != NULL);
  addNode->data = item;
  lp->head->prev->next = addNode;
  addNode->next = lp->head; //set the pointers for the new node
  addNode->prev = lp->head->prev;
  lp->head->prev = addNode;
  lp->count++; //add one to count since you added a new node
  return;
}

void *removeFirst(LIST *lp){
  assert(lp != NULL && lp->count > 0);
  NODE* toBeDeleted = lp->head->next;
  void* copy = toBeDeleted->data;
  lp->head->next = toBeDeleted->next;//re-adjust the deleted node's pointers
  toBeDeleted->next->prev = lp->head;
  free(toBeDeleted);
  lp->count--;//-1 to the amount of items in the list
  return copy;
}

void *removeLast(LIST *lp){
  assert(lp != NULL && lp->count > 0);
  NODE* toBeDeleted = lp->head->prev;
  void *copy = toBeDeleted->data;
  lp->head->prev = toBeDeleted->prev;//re-adjust the deleted node's pointers
  toBeDeleted->prev->next = lp->head;
  free(toBeDeleted);
  lp->count--;//-1 to the amount of items in the list
  return copy;
}

void *getFirst(LIST *lp){//returns the data of the first node
  assert(lp != NULL && lp->count > 0);
  return lp->head->next->data;
}

void *getLast(LIST *lp){//returns the data of the last node
  assert(lp != NULL && lp->count > 0);
  return lp->head->prev->data;
}

void removeItem(LIST *lp, void *item){
  assert(lp != NULL);
  if(lp->count > 0){
    NODE* checker = lp->head->next;
    while(checker != lp->head){
      if((*lp->compare)(checker->data, item) == 0){ //change the pointers if a match is found
	checker->prev->next = checker->next;
	checker->next->prev = checker->prev;
	free(checker);
	lp->count--;
	break;
      }
      else{ //if they do not match, keep traversing
	checker = checker->next;
      }
    }
  }
  return;
}

void *findItem(LIST *lp, void *item){
  assert(lp != NULL);
  if(lp->count > 0){
    NODE* checker = lp->head->next;
    while(checker != lp->head){//go through the entire last to search for item
      if((*lp->compare)(checker->data, item) == 0){//compare each node to what we're looking for
	return checker->data;
      }
      else{
	checker = checker->next; //if they do not match, keep traversing
      } 
    }
  }
  return NULL; //return NULL if nothing is found
}

void *getItems(LIST *lp){
  assert(lp != NULL);
  void **array = malloc(sizeof(void*)*lp->count);//allocate an array with a size of the amount of nodes present in the list
  assert(array != NULL);
  int i = 0;
  NODE* checker = lp->head->next;
  while(checker != lp->head){//traverse through linked list and copy data to new array
    array[i++] = checker->data;
    checker = checker->next;
  }
  return array;
}
