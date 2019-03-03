//implementation of an array where the index is equal to their id for application #2
#include "data.h"

struct node{//each student is essentially a node
  int id;
  int age;
};

struct class{
  NODE **student;//student node
  int count;//keeps track of students currently in list
  int length;//max number of students allowed
};

CLASS* createDataSet(int maxStudents){
  CLASS *cList = malloc(sizeof(CLASS));
  assert(cList != NULL);
  cList->count = 0;//starts with no students in the class
  cList->length = maxStudents;//class capped at 3000
  cList->student = malloc(sizeof(NODE*)*maxStudents);//must allocate enough spots for the max number of students
  assert(cList->student != NULL);
  for(int i = 0; i < maxStudents; i++){//allocate memory for each node in the array
    cList->student[i] = malloc(sizeof(NODE));
    assert(cList->student[i] != NULL);
  }
  return cList;
}

void destroyDataSet(CLASS* cl){
  assert(cl != NULL);
  for(int i = 0; i < cl->length; i++){
    if(cl->student[i] == NULL){
      free(cl->student[i]);//free each student's info
    }
  }
  free(cl->student);
  free(cl);//free the ADT
  return;
}

int searchID(CLASS* cl, int matchID){
  assert(cl != NULL);
  printf("Searching for ID: %d\n", matchID);
  if(cl->student[matchID]->id == matchID){//if the data matches, return that index
    return matchID;
  }
  return -1;//return -1 if nothing is found
}

void insertion(CLASS* cl, int insertID, int insertAge){
  assert(cl != NULL && cl->count < cl->length);//cannot add a student if the class is full
  cl->student[insertID]->id = insertID;//insert the new student to the desired spot with the respective created ID and age
  cl->student[insertID]->age = insertAge;
  printf("Student ID: %d, Age: %d\n", cl->student[insertID]->id, cl->student[insertID]->age);//print out each student when you add them
  cl->count++;//increase amount of students in class by 1
  return;
}

void deletion(CLASS* cl, int deleteID){
  assert(cl != NULL);
  int index = searchID(cl, deleteID);
  if(index > 0){
    puts("Deleted student found!");
    printf("Deleted Student ID: %d, Age: %d\n", cl->student[index]->id, cl->student[index]->age);//print out the deleted student's info
    free(cl->student[index]);
    cl->count--;//decrease student count by 1 since you deleted one
  }
  else{
    puts("No student was deleted!");
  }
  return;
}
