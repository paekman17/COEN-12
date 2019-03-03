/*
Ethan Paek
Lab #6
Wednesday Sessions, March 14th, 2018
This function reads in the amount of unique and odd number of words in a text file through a hash table with void pointers and utilizes quick sort for the getElements function
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#define empty 0
#define filled 1
#define removed 2

static int search(SET* sp, void* elt, bool* found);
static int partition(SET* sp, void** elts, int low, int high);
static void quicksort(SET* sp, void** elts, int low, int high);

struct set{//an abstract data type that can store certain values, without any particular order, and no repeated values
  void** data;//address of char within array
  char* flag;//keep track if a slot in the hash table is empty, filled, or removed
  int length;//max limit of array
  int count;//number of elements present in array
  int (*compare)();//provided through the interface
  unsigned (*hash)();//provided through the interface
};

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){//create a set, O(n)
  SET *sp = (SET*)malloc(sizeof(SET));
  assert(sp != NULL);//assert the set and ensure that the pointer exists
  sp->count = 0;
  sp->length = maxElts;
  sp->compare = compare;
  sp->hash = hash;
  sp->data = malloc(sizeof(void*)*maxElts);
  sp->flag = (char*)malloc(sizeof(char)*maxElts);
  assert(sp->data != NULL && sp->flag != NULL);//assert the chars
  for(int i = 0; i < sp->length; i++){//make every single slot in the hash table as empty
    sp->flag[i] = empty;
  }
  return sp;//return the set
}

void destroySet(SET *sp){//destroy the set, O(n)
  assert(sp != NULL);
  for(int i = 0; i < sp->count; i++){
    if(sp->data[i] == NULL){
      free(sp->data[i]);//must free each and every char in the set
    }
  }
  free(sp->data);//free data char pointer
  free(sp->flag);//free flag char pointer
  free(sp);//free the entire set
  return;
}

int numElements(SET *sp){//count how many elements are currently in the set, O(1)
  assert(sp != NULL);
  return sp->count;//count tells how many elements are in the set
}

void addElement(SET *sp, void *elt){//insert an element into the set, O(1)
  assert(sp != NULL && elt != NULL && sp->count < sp->length);//count should never be larger than the size of the array
  bool find = false;
  int index = search(sp, elt, &find);
  if(find == false){//only allocate memory if it's a unique word not already present in the set
    sp->data[index] = elt;//allocate memory in the specific section of the hash table that was searched
    sp->flag[index] = filled;
    sp->count++;
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
  sp->flag[index] = removed;//change the marker to removed
  //we cannot free the void** since it is not a copy
  sp->count--;//one less element in the hash table
  return;
}

void *findElement(SET *sp, void *elt){//search whether a specific element is in the set, O(1)
  assert(sp != NULL && elt != NULL);
  bool find = false;
  int index = search(sp, elt, &find);
  if(find == false){
    return NULL;//return NULL if there is no match
  }
  return sp->data[index];
}

void *getElements(SET *sp){//allocate and return an array of elements in the set pointed to by a pointer, O(n)
  assert(sp != NULL);
  void** elts = malloc(sizeof(void*)*sp->count);
  assert(elts != NULL);
  int i, j;
  for(i = 0, j = 0; i < sp->length; i++){
    if(sp->flag[i] == filled){
      elts[j++] = sp->data[i];
    }
  } 
  quicksort(sp, elts, 0, sp->count - 1);//use quick sort to sort the copied array
  return elts;
}

static int search(SET *sp, void *elt, bool* find){//returns the location of an element within an array, O(n)
  assert(sp != NULL && elt != NULL);
  int index = (*sp->hash)(elt) % sp->length;
  int trials = 0;//worst case of checking every single element in table
  int deletedSlot = -1;
  while(trials < sp->length){
    if(sp->flag[index] == empty){//if it's empty, return the index
      *find = false;
      return deletedSlot != -1 ? deletedSlot : index;
    }
    else if(sp->flag[index] == removed){//if the index is on a slot that has been deleted, just increase the index by one and check again
      trials++;
      if(deletedSlot == -1){//remember the first deleted slot and return this first
	deletedSlot = index;
      }
      index = (index + 1) % sp->length;
    }
    else{
      if((*sp->compare)(sp->data[index], elt) == 0){ //compare using the compare function
	*find = true;
	return index; //return index and found to true if the element is present in the hash table
      }
      else{ //if they don't match, increase the index by one again
	index = (index + 1) % sp->length;
	trials++;
      }
    }
  }
  *find = false;
  return deletedSlot;
}

static int partition(SET* sp, void** elts, int low, int high){
  assert(sp != NULL);
  void* pivot = elts[high];//start at beginning index to partition
  int smaller = low - 1;  //index of smaller element
  for (int i = low; i <= high - 1; i++){
    if ((*sp->compare)(elts[i], pivot) <= 0){//if the element in the array is less than or equal to the pivot, swap
      smaller++;//increment index of smaller element
      void* temp = elts[smaller];
      elts[smaller] = elts[i];
      elts[i] = temp;
    }
  }
  void* swap = elts[smaller + 1];//swap the next element from smaller and return that index
  elts[smaller + 1] = elts[high];
  elts[high] = swap;
  return smaller + 1;
}

static void quicksort(SET* sp, void** elts, int low, int high){
  assert(sp != NULL);
  if(low < high){//when the "magic walls" collide, stop partitioning
    int partitionIndex = partition(sp, elts, low, high);
    quicksort(sp, elts, low, partitionIndex - 1);//since array is now divided into two (one is all lower than partitionIndex and other is higher than partitionIndex), recursively partition those those two parts
    quicksort(sp, elts, partitionIndex + 1, high);
  }
  return;
}
