/*Ethan Paek, January 10th, 2017
Lab #1
Lab Session 3 (Wednesdays) */
#include <string.h>
#include <stdio.h>
#define MAX_WORD_LENGTH 30

void read_file(char* fileName);

int main(int argc, char* argv[]){
  if(argc != 2){//quit the program if you don't have the file
    puts("The name of the file is missing! Lo siento.");
    return 0;
  }
  else{
    read_file(argv[1]);
  }
  return 0;
}

void read_file(char* fileName){
  FILE* fp = fopen(fileName, "r");//open the file
  int number = 0;
  char* input = malloc(20);
  if(fp == NULL){//quit the program if you are not able to open file
    puts("File cannot be opened. Smh fam");
    return;
  }
  while(fscanf(fp, "%s", input) > 0){
    if(strlen(input) <= MAX_WORD_LENGTH){//if the word is less than or equal to max word length
      number++;//count the words
    }
  }
  printf("%d total words\n", number);//return the number of words
  fclose(fp);//close the file
  return;
}
