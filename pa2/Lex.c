/*
Student: Nixon Duong
CruzID: niduong
Professor: Patrick Tantalo
Course: CMPS101
Programming Assignment: PA2
Description: Opens and reads files contents into an char *array. Indirectly sorts the array using service provided
from List.c. Writes the sorted version of the array onto an outfile.
File: Lex.c
Dependencies: List.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
    
    int count=0;
    FILE *in, *out;
    char line[MAX_LEN];
 
    // check command line for correct number of arguments
    if(argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if(in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    while(fgets(line, MAX_LEN,in) != NULL){ // counts the number of lines in the file inorder to allocate space 
        count++;
    }

    // acts as a reset method to start back at the beginning of the file
    fclose(in);
    in = fopen(argv[1], "r");

    // creates a mathix
    char matrix[count - 1][MAX_LEN];
    int lineA = -1;

    //adds data from the inputfile into the matrix
    while(fgets(line,MAX_LEN,in) != NULL){
        strcpy(matrix[++lineA],line);
    }

    //Sorting indirectly using list(insertion sort)
    List L = newList();
    append(L,0);
    char *temp;
    for(int i =1;i<count;i++){
        moveBack(L);
        temp = matrix[i];
        while((index(L)>=0) && strcmp(temp, matrix[get(L)])<= 0){
            movePrev(L);
        }
        if(index(L) >= 0){
            insertAfter(L,i);
        }
        else{
            prepend(L,i);
        }
    }

    //outfiles sorted input
    moveFront(L);
    for(int i=0;i<count;i++){
        fprintf(out,"%s\n",matrix[get(L)]);
        moveNext(L);
    }
    
    //closes files and frees List
    fclose(in);
    fclose(out);
    freeList(&L);
    
    return(0);
}