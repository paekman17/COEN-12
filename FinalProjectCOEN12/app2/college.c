/*
Ethan Paek
Dr. Yuhong Liu
COEN 12
March 11th, 2017
This program simulates a college admission enrollment process by searching through a given id
Application #2
*/
#include "data.h"
#define MAXSTUDENTS 3000

int previousID = 0;//used to keep track of previous student's ID

int main(){
  CLASS* app2;
  srand(time(NULL));//necessary to generate random numbers
  app2 = createDataSet(MAXSTUDENTS);
  int studentNumber = 0;
  puts("Adding Students:");
  while(studentNumber < 1000){//add 1000 students to the class
    int randomID = (rand() % 2) + 1;//ranges between 1 and 2
    int randomAge = (rand() % 13) + 18;//ranges between 18 and 30
    previousID += randomID;//determining a new student's ID according to lab document
    insertion(app2, previousID, randomAge);
    studentNumber++;//move on to the next student
  }  
  int deleteID = (rand() % 2000) + 1;//random id ranging from 1 - 2000
  deletion(app2, deleteID);//delete the student if found in the list
  destroyDataSet(app2);//destroy the entire data set
}
