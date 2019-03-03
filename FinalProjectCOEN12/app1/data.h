#ifndef DATA_H
#define DATA_H

#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct student STUDENT;
typedef struct list LIST;
typedef struct class CLASS;

CLASS* createDataSet(int maxStudents);
void destroyDataSet(CLASS* cl);
int searchAge(CLASS* cl, int matchAge);
void insertion(CLASS* cl, int insertID, int insertAge);
void deletion(CLASS* cl, int deleteAge);
int maxAgeGap(CLASS* cl);

#endif
