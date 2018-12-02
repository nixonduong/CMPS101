/*
Student: Nixon Duong
CruzID: niduong
Professor: Patrick Tantalo
Course: CMPS101
Programming Assignment: PA5
Description: Provides an interface for clients
File: List.h
Clients: Graph.h
*/
#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
//Exported type 
typedef struct ListObj* List;
//Constructors-Deconstructors
List newList(void);
void freeList(List* pL);
//Access functions
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);
//Manipulation functions
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);
//Other operations
void printList(FILE* out, List L);
List copyList(List L);

#endif