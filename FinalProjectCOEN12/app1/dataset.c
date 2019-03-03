//implementation of an array of linked lists for application #1
#include "data.h"

struct student{
  STUDENT* next;//pointers to traverse through each list
  STUDENT* prev;
  int age;//student info
  int id;
};

struct list{
  int ageCount;//keep track of how many students have the desired age
  STUDENT *head;//dummy node
};

struct class{
  LIST **array;//use an array of structs to hold all of the students based on age
  int studentCount;//keeps track of students currently in list
  int length;//max number of students allowed
};

CLASS* createDataSet(int maxStudents){
  CLASS *cList = malloc(sizeof(CLASS));
  assert(cList != NULL);
  cList->studentCount = 0;//starts with no students in the class
  cList->length = maxStudents;//class capped at 3000
  cList->array = malloc(sizeof(LIST*)*13);//need 13 lists for 13 different ages
  for(int i = 0; i < 13; i++){//set up 12 lists for each respective age
    cList->array[i] = malloc(sizeof(LIST));//need to multiply by max students in case all students have the same age
    cList->array[i]->head = malloc(sizeof(STUDENT));
    assert(cList->array[i]->head != NULL);
    cList->array[i]->head->next = cList->array[i]->head;//set head pointers equal to itself
    cList->array[i]->head->prev = cList->array[i]->head;
    cList->array[i]->ageCount = 0;//should be 0 students in each respective linked list
  }
  return cList;
}

void destroyDataSet(CLASS* cl){
  assert(cl != NULL);
  for(int i = 0; i < 13; i++){
    if(cl->array[i]->ageCount > 0){//go through each list and free all nodes if they have something
      STUDENT* pDel;
      STUDENT* pPrev = cl->array[i]->head->prev;
      do{
	pDel = pPrev;
	pPrev = pDel->prev;
	free(pDel);
      }while(pDel != cl->array[i]->head);
    }
    free(cl->array[i]);
  }
  free(cl);//free the ADT
  return;
}

int searchAge(CLASS* cl, int matchAge){
  assert(cl != NULL);
  int index = matchAge - 18;//ex. someone who is 18 would be stored at index 0
  printf("Searching for Age: %d\n", matchAge);
  if(cl->array[index]->ageCount > 0){
    return 1;//if it is found, return 1
  }
  return 0;//if there are no students with that age, return 0
}

void insertion(CLASS* cl, int insertID, int insertAge){
  assert(cl != NULL && cl->studentCount < cl->length);//cannot add a student if the class is full
  STUDENT* addNode = malloc(sizeof(STUDENT));//allocating memory for the new node
  assert(addNode != NULL);
  int index = insertAge - 18;//ex. someone who is 18 would be stored at index 0
  addNode->id = insertID;//assigning the new node's data equal to the randomly generated age and id
  addNode->age = insertAge;
  cl->array[index]->head->prev->next = addNode;//set the new node to the end of the list
  addNode->next = cl->array[index]->head;
  addNode->prev = cl->array[index]->head->prev;
  cl->array[index]->head->prev = addNode;
  cl->array[index]->ageCount++;//add one to the amount of students with that age
  printf("Student ID: %d, Age: %d\n", addNode->id, addNode->age);
  cl->studentCount++;//increase amount of students in class by 1
  return;
}

void deletion(CLASS* cl, int deleteAge){
  assert(cl != NULL);
  int find = searchAge(cl, deleteAge);
  if(find == 1){
    int index = deleteAge - 18;
    puts("Deleted student(s) found!");
    int trials = 0;
    STUDENT *printNode = cl->array[index]->head->next;
    while(trials != cl->array[index]->ageCount){//print out each of the deleted nodes
      printf("Deleted Student ID: %d, Deleted Age: %d\n", printNode->id, printNode->age);
      printNode = printNode->next;
      trials++;
    }
    STUDENT* pDel = cl->array[index]->head->next;//have to do 2 separate nodes since they will be at different locations
    while(pDel != cl->array[index]->head){//traverse the respective list and free everything
      cl->array[index]->head->next = pDel->next;
      free(pDel);
      pDel = cl->array[index]->head->next;
      cl->studentCount--;//delete from the total number of students
    }
    cl->array[index]->ageCount = 0;//no one left in the respective list now
    cl->array[index]->head->next = cl->array[index]->head;//reset the head's pointers
    cl->array[index]->head->prev = cl->array[index]->head;    
  }
  return;
}

int maxAgeGap(CLASS* cl){
  assert(cl != NULL);
  int minIndex = 0;
  int maxIndex = 12;
  while(cl->array[minIndex]->ageCount == 0){//start from index 0 and go through array until you find a non-empty list
    minIndex++;
  }
  while(cl->array[maxIndex]->ageCount == 0){//same as above but starts from the end of the array
    maxIndex--;
  }
  return (maxIndex - minIndex);//since arrays start at 0, add one
}
