/*
Ethan Paek
Lab #5
Wednesday Sessions
This is a program that utilizes huffman coding which encodes data in an efficient manner to save memory

Process for Huffman Coding:
1. Read the file (file1) and count the frequency of each character
2. Create tree (nodes) for each char that appears in the file
3. Build Huffman Tree by repeatedly combining the least frequent nodes (using the priority queue!)
4. Print out number of bits for each char
*/
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "pqueue.h"
#include "pack.h"

typedef struct node NODE;

static void readFile(char* fileName);
static NODE* mkNode(int data, NODE* left, NODE* right);
static int depth(NODE* np);
static int nodeCmp(NODE* np1, NODE* np2);

int ascii[257];//index is each individual ascii character; value is equal to frequency
NODE* nodes[257];//essentially will become the priority queue

int main(int argc, char* argv[]){
  if(argc == 2){
    puts("Missing and/or added insufficient number of files!");
    return 0;
  }
  else{
    readFile(argv[1]);
  }
  PQ *pq = createQueue(nodeCmp);//create the priority queue 
  for(int i = 0; i < 256; i++){//make each non-zero frequency character into a leaf and add it to the priority queue
    if(ascii[i] > 0){
      nodes[i] = mkNode(ascii[i], NULL, NULL);
      addEntry(pq, nodes[i]);
    }
  }
  nodes[256] = mkNode(0, NULL, NULL);//make the last spot equal to 0 for EOF to ensure that the priority queue is never truly empty
  addEntry(pq, nodes[256]);//gotta add the zero leaf as well
  while(numEntries(pq) > 1){//keep combining the least frequent nodes until you are left with one node in the priority queue (a.k.a the huffman tree)
    NODE* left = removeEntry(pq);//smallest nodes will always be the root of the min heap
    NODE* right = removeEntry(pq);
    NODE* parent = mkNode(left->count + right->count, left, right);
    addEntry(pq, parent);
  }
  for(int j = 0; j < 256; j++){ //print out the bits used for each character in text file
    if(nodes[j] != NULL){
      printf(isprint(j) ? "%c" : "%03o", j);
      printf(": %d x %d bits = %d bits\n", ascii[j], depth(nodes[j]), ascii[j]*depth(nodes[j]));
    }
  }
  pack(argv[1], argv[2], nodes);
  destroyQueue(pq);
  return 0;
}

static void readFile(char* fileName){
  FILE* fp = fopen(fileName, "r");
  if(fp == NULL){//return the function if the file cannot be opened
    puts("File cannot be opened. Smh fam");
    return;
  }
  int x = getc(fp);//will continously retrieve the character at spot in file in terms of ASCII (0 - 255)
  while(x != EOF){//add one to frequency of character to int array
    ascii[x]++;
    x = getc(fp);
  }
  fclose(fp);
  return;
}

static NODE* mkNode(int data, NODE* left, NODE* right){
  NODE* root = malloc(sizeof(NODE));
  assert(root != NULL);
  root->count = data;//set the number of occurences to the node's data
  root->parent = NULL;//no parent is set yet
  if(left != NULL){//if left and right are not NULL, they should be the new node's children
    left->parent = root;
  }
  if(right != NULL){
    right->parent = root;
  }
  return root;
}

static int depth(NODE* np){ //return the depth of a given node
  assert(np != NULL);
  if(np->parent == NULL){
    return 0;
  }
  return depth(np->parent) + 1;
}

static int nodeCmp(NODE* np1, NODE* np2){//return the bigger of the two nodes
  assert(np1 != NULL && np2 != NULL);
  return (np1->count < np2->count) ? -1 : (np1->count > np2->count);
}
