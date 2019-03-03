#ifndef DATA_H
#define DATA_H

#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node NODE;
typedef struct class CLASS;

CLASS* createDataSet(int maxStudents);
void destroyDataSet(CLASS* cl);
int searchID(CLASS* cl, int matchID);
void insertion(CLASS* cl, int insertID, int insertAge);
void deletion(CLASS* cl, int deleteID);

#endif
