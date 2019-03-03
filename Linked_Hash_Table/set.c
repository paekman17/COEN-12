/*
Ethan Paek
Lab #4
Wednesday Sessions, February 21st, 2018
This is a program that inserts data into a hash table but inserts into a linked list if there is a collision
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "set.h"
#include "list.h"
#define alpha 20

static int search(SET* sp, void* elt, bool* found);

struct set{//an abstract data type that can store certain values, without any particular order, and no repeated values
  LIST** data;//address of char within array
  int length;//max limit of array
  int count;//number of elements present in array
  int (*compare)();//provided through the interface
  unsigned (*hash)();//provided through the interface
};

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){//create a set, O(n)
  SET *sp = (SET*)malloc(sizeof(SET));
  assert(sp != NULL);//assert the set and ensure that the pointer exists
  sp->count = 0;
  sp->length = ceil(maxElts/alpha); //derived from lab instructions
  sp->compare = compare;
  sp->hash = hash;
  sp->data = malloc(sizeof(LIST*)*sp->length);
  assert(sp->data != NULL);//assert the char
  for(int i = 0; i < sp->length; i++){//make a linked list in each slot of the hash table
    sp->data[i] = createList(sp->compare);
  }
  return sp;//return the set
}

void destroySet(SET *sp){//destroy the set, O(n)
  assert(sp != NULL);
  for(int i = 0; i < sp->length; i++){
    destroyList(sp->data[i]);//destroy each linked list one by one
  }
  free(sp->data);//free data char pointer
  free(sp);//free the entire set
  return;
}

int numElements(SET *sp){//count how many elements are currently in the set, O(1)
  assert(sp != NULL);
  return sp->count;//count tells how many elements are in the set
}

void addElement(SET *sp, void *elt){//insert an element into the set, O(1)
  assert(sp != NULL && elt != NULL);
  bool find = false;
  int index = search(sp, elt, &find);
  if(find == false){//only allocate memory if it's a unique word not already present in the set
    addLast(sp->data[index], elt);//add the element to the end of the respective linked list
    sp->count++;//add one to count
  } 
  return;
}

void removeElement(SET *sp, void *elt){//delete an element from the set, O(1)
  assert(sp != NULL && elt != NULL);
  bool find = false;
  int index = search(sp, elt, &find);
  if(find == false){//do nothing if the element is not found
    return;
  }
  removeItem(sp->data[index], elt);//remove the item from the linked list
  sp->count--;//remove one from the count
  return;
}

void *findElement(SET *sp, void *elt){//search whether a specific element is in the set, O(1)
  assert(sp != NULL && elt != NULL);
  bool find = false;
  int index = search(sp, elt, &find);
  if(find == false){
    return NULL;//return NULL if there is no match
  }	
  return findItem(sp->data[index], elt);
}

void *getElements(SET *sp){//allocate and return an array of elements in the set pointed to by a pointer, O(n)
  assert(sp != NULL);
  void** elts = malloc(sizeof(void*)*sp->count);
  assert(elts != NULL);
  int trials = 0;
  for(int i = 0; i < sp->length; i++){//traverse the entire list of linked lists
    void** copyList = getItems(sp->data[i]);
    for(int j = 0; j < numItems(sp->data[i]); j++){//traverse each individual linked list
      elts[trials] = copyList[j];//copy the data
      trials++;//increment in the array you are copying to
    }
  } 
  return elts;
}

static int search(SET *sp, void *elt, bool* find){//returns the location of an element within an array, O(n)
  assert(sp != NULL && elt != NULL);
  int index = (*sp->hash)(elt) % sp->length;
  if(findItem(sp->data[index], elt) != NULL){//look for the item in the respective linked list
    *find = true;//return true if it is found
    return index;
  }
  *find = false;//return false if it's not found
  return index;
}
