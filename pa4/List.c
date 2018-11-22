/*
Student: Nixon Duong
CruzID: niduong
Professor: Patrick Tantalo
Course: CMPS101
Programming Assignment: PA4
Description: Provides a bi-directional list to clients
File: List.c
Clients: Graph.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;  

Node newNode(int data){
	Node node = malloc(sizeof(NodeObj));
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return(node);
}

void freeNode(Node *pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN = NULL;
	}
}

List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);   
}

//Access functions
int length(List L){// returns the number of elements in the List
	if(L==NULL){
		printf("List Error: called length() on NULL List reference\n");
		exit(1);
	}
	else{
		return(L->length);
	}
}


void freeList(List *pL){
	if(pL!=NULL && *pL!=NULL){
		while(length(*pL) > 0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}


int index(List L){// if cursor defined, returns index of cursor, else -1
	if(L==NULL){
		printf("List Error: called index() on NULL List reference\n");
		exit(1);
	}
	else{
		return(L->index); // if cursor isnt defined, the index is -1
	}
}

int front(List L){// returns the front element Pre: len > 0
	if(L==NULL){
		printf("List Error: called front() on NULL List reference\n");
		exit(1);
	}
	else{
		if(L->length >0){
			return(L->front->data);
		}
		return(-1);
	}
}

int back(List L){// return the back element Pre: len > 0
	if(L==NULL){
		printf("List Error: called back() on NULL List reference\n");
		exit(1);
	}	
	else{
		if(L->length > 0){
			return(L->back->data);
		}
		return(-1);
	}
}

int get(List L){ // Returns cursor element Pre: len > 0 , index >=0
	if(L==NULL){
		printf("List Error: called get() on NULL List reference\n");
		exit(1);
	}
	else{
		if(L->length>0 && L->index>=0){
			return(L->cursor->data);
		}
		return(-1);
	}
}

int equals(List A, List B){// Returns 1 if List A is equal to List B, else 0
	int equal = 0;
	Node X = NULL;
	Node Y = NULL;
	if(A==NULL || B==NULL){
		printf("List Error: called equals() on NULL List reference\n");
		exit(-1);
	}
	equal = (A->length == B->length);
	X = A->front;
	Y = B->front;
	while(equal && X!=NULL){
		equal = (X->data == Y->data);
		X = X->next;
		Y = Y->next;
	}
	return(equal);
}

//Manipulation functions
void clear(List L){// resets the list
	if(L==NULL){
		printf("List Error: called clear() on NULL List reference\n");
		exit(-1);
	}
	else{
		while(length(L) > 0){
			deleteFront(L);
		}
		L->front = L->back = L->cursor = NULL;
		L->length = 0;
		L->index = -1;
	}
}

void moveFront(List L){// if list non-empty, place cursor on front node, else does nothing
	if(L==NULL){
		printf("List Error: called moveFront() on NULL List reference\n");
		exit(-1);
	}
	else{
		if(L->length > 0){
			L->cursor = L->front;
			L->index = 0;
		}
	}
}

void moveBack(List L){// if list non-empty, place cursor on back node, else does nothing
	if(L==NULL){
		printf("List Error: called moveBack() on NULL List reference\n");
		exit(-1);
	}
	else{
		if(L->length >0){
			L->cursor = L->back;
			L->index = L->length - 1;
		}
	}
}

void movePrev(List L){// if cursor is defined and not front, move cursor prev, if defined and at front, cursor is undefined
	if(L==NULL){
		printf("List Error: called movePrev() on NULL List reference\n");
		exit(-1);
	}
	if(L->cursor!=NULL){
		if(L->cursor != L->front){
			L->cursor = L->cursor->prev;
		}
		else{
			L->cursor = NULL;
		}
		L->index--;
	}
	
}
void moveNext(List L){// if cursor is defined and not back, move cursor back, if defined and at back, cursor is undefined
	if(L==NULL){
		printf("List Error: called moveNext() on NULL List reference\n");
		exit(-1);
	}
	if(L->cursor!=NULL){
		if(L->cursor != L->back){
			L->cursor = L->cursor->next;
			L->index++;
		}
		else{
			L->cursor = NULL;
			L->index = -1;
		}
	}
}

void prepend(List L, int data){// insert new element into the list, if list is non-empty, element goes in the front
	if(L==NULL){
		printf("List Error: called prepend() on NULL List reference\n");
		exit(-1);
	}
	else{
		Node node = newNode(data);
		if(L->length == 0){
			L->front = L->back = node;
		}
		else{
			node->next = L->front;
			L->front->prev = node;
			L->front = node;
		}
		L->index++;
		L->length++;
	}
}

void append(List L, int data){// insert new element into the list, if list is non-empty, element goes in the back
	if(L==NULL){
		printf("List Error: called append() on NULL List reference\n");
		exit(-1);
	}
	else{
		Node node = newNode(data);
		if(L->length == 0){
			L->front = L->back = node;
		}
		else{
			node->prev = L->back;
			L->back->next = node;
			L->back = node;
		}
		L->length++;
	}
}

void insertBefore(List L, int data){// insert new element before cursor. Pre: len > 0, index >=0
	if(L==NULL){
		printf("List Error: called insertBefore() on NULL List reference\n");
		exit(-1);
	}
	else{
		if(L->length > 0 && L->index >=0){
			if(L->cursor == L->front){
				prepend(L,data);
			}
			else{
				Node node = newNode(data);
				node->next = L->cursor;
				L->cursor->prev->next = node;
				node->prev = L->cursor->prev;
				L->cursor->prev = node;
				L->length++;
				L->index++;
			}
		}
	}
}

void insertAfter(List L, int data){// insert new element after cursor. Pre: len > 0, index >=0
	if(L==NULL){
		printf("List Error: called insertAfter() on NULL List reference\n");
		exit(-1);
	}
	else{
		if(L->length > 0 && L->index >=0){
			if(L->cursor == L->back){
				append(L,data);
			}
			else{
				Node node = newNode(data);
				node->prev = L->cursor;
				node->next = L->cursor->next;
				L->cursor->next->prev = node;
				L->cursor->next = node;
				L->length++;
			}
		}
	}
}

void deleteFront(List L){// deletes the front element. Pre: len > 0
	if(L==NULL){
		printf("List Error: called deleteFront() on NULL List reference\n");
		exit(-1);
	}
	else{
		if(L->length == 0){
			printf("deleteFront() on emptyList");
			exit(-1);
		}
		if(L->length > 0){
			if(L->length == 1){
				freeNode(&L->front);
				L->cursor = L->front = L->back = NULL;
				L->index = -1;
			}
			else{
				Node temp = NULL;
				if(L->cursor == L->front){
					temp = L->front;
					L->front = L->front->next;
					L->front->prev = NULL;
					L->cursor = NULL;
					L->index = -1;
				}
				else{
					temp = L->front;
					L->front = L->front->next;
					L->front->prev = NULL;
					if(L->cursor!=NULL){
						L->index--;
					}
				}
				freeNode(&temp);
			}
			L->length--;
		}
	}
}

void deleteBack(List L){// deletes the back element. Pre: len > 0
	if(L==NULL){
		printf("List Error: called deleteBack() on NULL List reference\n");
		exit(-1);
	}
	else{
		if(L->length == 0){
			printf("deleteBack() on emptyList");
			exit(-1);
		}
		if(L->length > 0){
			Node temp = NULL;
			if(L->length == 1){
				temp = L->back;
				L->cursor = L->front = L->back = NULL;
				L->index = -1;
			}
			else{
				if(L->cursor == L->back){
					L->cursor = NULL;
					L->index = -1;
				}
				temp = L->back;
				L->back = L->back->prev;
				L->back->next = NULL;
			}
			L->length--;
			freeNode(&temp);
		}
	}
}

void delete(List L){// deletes the cursor element, sets cursor to undefeined and index to -1 Pre: length > 0, index >=0
	if(L==NULL){
		printf("List Error: called delete() on NULL List reference\n");
		exit(-1);
	}
	else{
		if(L->length == 0){
			printf("delete() on emptyList");
			exit(-1);
		}
		if(L->length>0 && L->index >=0){
			if(L->cursor == L->front){
				deleteFront(L);
			}
			else if(L->cursor == L->back){
				deleteBack(L);
			}
			else{
				L->cursor->prev->next = L->cursor->next;
				L->cursor->next->prev = L->cursor->prev;
				L->length--;
			}
			freeNode(&L->cursor);
			L->index = -1;
		}
	}
}

//Other operations
void printList(FILE* out, List L){// prints list to file pointed by out, formatted as a space-separed string
	if(L==NULL){
		printf("List Error: called printList() on NULL List reference\n");
		exit(-1);
	}
	else{
		Node iterator = L->front;
		while(iterator!=NULL){
			fprintf(out,"%d ",iterator->data);
			iterator = iterator->next;
		}
	}
}
List copyList(List L){
	List list = newList();
	if(L==NULL){
		printf("List Error: called copyList() on NULL List reference\n");
		exit(-1);
	}
	else{
		if(L->length!=0){
			Node iterator = L->front;
			while(iterator!=NULL){
				append(list,iterator->data);
				iterator = iterator->next;
			}
			return list;
		}
	}
	return list;
}
