/*
Ethan Paek
Lab #2
Wednesday Sessions, January 24th, 2018
This function implements binary searching by organizing data
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

static int search(SET *sp, char *elt, bool *found);

struct set{//an abstract data type that can store certain values, without any particular order, and no repeated values
  char** data;//address of char within array
  int length;//max limit of array
  int count;//number of elements present in array
};

SET *createSet(int maxElts){//create a set
  SET *sp = (SET*)malloc(sizeof(SET));
  assert(sp != NULL);//assert the set and ensure that the pointer exists
  sp->count = 0;
  sp->length = maxElts;
  sp->data = (char**)malloc(sizeof(char*)*maxElts);
  assert(sp->data != NULL);//assert the chars
  return sp;//return the set
}

void destroySet(SET *sp){//destroy the set
  assert(sp != NULL);
  for(int i = 0; i < sp->count; i++){
    free(sp->data[i]);//must free each and every char in the set
  }
  free(sp->data);//free the char pointer
  free(sp);//free the entire set
  return;
}

int numElements(SET *sp){//count how many elements are currently in the set
  assert(sp != NULL);
  return sp->count;//count tells how many elements are in the set
}

void addElement(SET *sp, char *elt){//insert an element into the set
  assert(sp != NULL && elt != NULL && sp->count <= sp->length);//count should never be larger than the size of the array
  bool find = false;
  int index = search(sp, elt, &find);
  if(find == false){//only allocate memory if it's a unique word not already present in the set
    for(int i = sp->count; i > index; i--){
      sp->data[i] = sp->data[i-1];//shift all elements down one slot
    }
    sp->data[index] = strdup(elt);//allocate memory for the last spot in count
    sp->count++;
  }
  return;
}

void removeElement(SET *sp, char *elt){//delete an element from the set
  assert(sp != NULL && elt != NULL);
  bool find = false;
  int index = search(sp, elt, &find);//find the index of the chosen element
  if(find == false){
    return;
  }
  for(int i = index; i < sp->count; i++){
    sp->data[i] = sp->data[i+1];//shift all of the elements by one since you deleted one
  }
  sp->count--;//decrease the count by 1 since you removed one element
  return;
}

char *findElement(SET *sp, char *elt){//search whether a specific element is in the set
  assert(sp != NULL && elt != NULL);
  bool find = false;
  int index = search(sp, elt, &find);
  if(find == false){
    return NULL;//return NULL if there is no match
  }
  return sp->data[index];//return the found element
}

char **getElements(SET *sp){//allocate and return an array of elements in the set pointed to by a pointer
  assert(sp != NULL);
  char** elements = (char**) malloc(sizeof(char*) * sp->count);
  elements = sp->data;//copy the contents of the original data
  return elements;
}

static int search(SET *sp, char *elt, bool* find){//returns the location of an element within an array
  assert(sp != NULL && elt != NULL);
  int lo, hi, mid;
  lo = 0;
  hi = sp->count - 1;//set the high value to be the max index possible
  while (lo <= hi){
    mid = (lo + hi)/2;
    if(strcmp(sp->data[mid], elt) > 0){//only look at the bottom half of the array now
      hi = mid - 1;
    }
    else if(strcmp(sp->data[mid], elt) < 0){//only look at the top half of the array now
      lo = mid + 1;
    }
    else{//return the index if found
      *find = true;
      return mid;
    }
  }
  *find = false;
  return lo;
}
