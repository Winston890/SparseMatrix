//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
// Credits to Patrick Tantalo for initial Queue ADT
// Winston Yi
// wyi10
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   void* data;
   Node next;
   Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   int index;
   int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List LL;
   LL = malloc(sizeof(ListObj));
   LL->front = LL->back = NULL;;
   LL->index = -1;
   LL->length = 0;
   return(LL);
}

// freeList()
// Frees all heap memory associated with List *pLL, and sets *pLL to NULL.
void freeList(List* pLL){
   if(pLL!=NULL && *pLL!=NULL) { 
      while( !isEmpty(*pLL) ) {
        deleteFront(*pLL); 
      }
      free(*pLL);
      *pLL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// index()
// Returns the index of the cursor. Returns -1 if cursor is undefined.
int index(List LL) {
	if (LL==NULL) {
      	    	printf("List Error: calling index() on NULL List reference\n");
     		exit(EXIT_FAILURE);
	}
	return LL->index;
}

// front()
// Returns the value at the front of LL.
// Pre: !isEmpty(LL)
void* front(List LL){
   if( LL==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(LL) ){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(LL->front->data);
}

// back()
// Returns the value at the back of LL.
// Pre: length()>0
void* back(List LL) {
	if (LL==NULL) {
      	    	printf("List Error: calling front() on NULL List reference\n");
     		exit(EXIT_FAILURE);
	}
	if (length(LL) == 0) {
      	    	printf("List Error: calling front() on NULL List reference\n");
     		exit(EXIT_FAILURE);
	}
	return (LL->back->data);
}

// get()
// Returns the cursor's element Node
// Pre: length() > 0, index >= 0
void* get(List LL) {
	if (LL==NULL) {
      	    	printf("List Error: calling get() on NULL List reference\n");
     		exit(EXIT_FAILURE);
	}
	if (isEmpty(LL)) {
      	    	printf("List Error: calling get() on NULL List reference\n");
     		exit(EXIT_FAILURE);
	}
	Node node = LL->front;
	for (int i = 0; i < index(LL); i++) {
		node = node->next;
	}
	return node->data;
}

// length()
// Returns the length of LL.
int length(List LL){
   if( LL==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(LL->length);
}

// isEmpty()
// Returns true (1) if LL is empty, otherwise returns false (0)
bool isEmpty(List LL){
   if( LL==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(length(LL)==0);
}



// Manipulation procedures ----------------------------------------------------

// clear()
// Clears the list

void clear(List LL) {
   if( LL==NULL ){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
	for (int i = length(LL); i > 0; i--) {
		deleteFront(LL);
	}
}

// set()
// Sets cursor's element's data
void set(List LL, void* x) {
   if( LL==NULL ){
      printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(LL)){
      printf("List Error: calling set() on empty list\n");
      exit(EXIT_FAILURE);
   }
	Node node = LL->front;
	for (int i = 0; i < index(LL); i++) {
		node = node->next;
	}
	node->data = x;
}

// moveFront
// Moves cursor to the front if list is nonempty
void moveFront(List LL) {
   if( LL==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(LL)) {
	   return;
   }
   LL->index = 0;
}

// moveBack
// Moves cursor to back if list is nonempty
void moveBack(List LL) { 
   if( LL==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (isEmpty(LL)) {
	   return;
   }
   LL->index = length(LL)-1;
}

// movePrev
// Moves cursor one step closer to the front of list
void movePrev(List LL) {
   if( LL==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (LL->index == -1) {
	   return;
   }
   LL->index -= 1;
}

// moveNext
// Moves cursor one step towards end of list
void moveNext(List LL) {
   if( LL==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (index(LL) == -1) {
	   return;
   }
   LL->index += 1;
   if (LL->index >= length(LL)) {
	   LL->index = -1;
   }
}

// append()
// Places new data at the back of LL.
void append(List LL, void* data)
{
   Node N = newNode(data);

   if( LL==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if( isEmpty(LL) ) { 
      LL->front = LL->back = N; 
   }else{ 
      LL->back->next = N; 
      N->prev = LL->back;
      LL->back = N; 
   }
   LL->length++;
}

// prepend()
// Places new node at beginning of list
void prepend(List LL, void* data) {
   if( LL==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
	Node N = newNode(data);
   if( isEmpty(LL) ) { 
      LL->front = LL->back = N; 
   }else{
      N->next = LL->front; 
      LL->front->prev = N; 
      LL->front = N;
   }
   LL->index +=1;
   LL->length += 1;
}

// insertBefore()
// Inserts element before cursor
void insertBefore(List LL, void* x) {
   if( LL==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(LL) ){
      printf("List Error: calling insertBefore() on an empty List\n");
      exit(EXIT_FAILURE);
   }
	Node runner = LL->front;
	for (int i = 0; i < index(LL); i++) {
		runner = runner->next;
	}
	if (runner->prev == NULL) {
		prepend(LL, x);
		return;
	} else {
	        Node node = newNode(x);
		node->next = runner;
		node->prev = runner->prev;
		runner->prev->next = node;
		node->next->prev = node;
	}
	LL->index += 1;
	LL->length += 1;
}

// insertAfter()
// Inserts element after cursor
void insertAfter(List LL, void* x) {
   if( LL==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(LL) ){
      printf("List Error: calling insertAfter() on an empty List\n");
      exit(EXIT_FAILURE);
   }
	Node runner = LL->front;
	for (int i = 0; i < index(LL); i++) {
		runner = runner->next;
	}
	if (runner->next == NULL) {
		append(LL, x);
		return;
	} else{	
	        Node node = newNode(x);
		node->prev = runner;
		node->next = runner->next;
		runner->next->prev = node;
		runner->next = node;
	}
	LL->length += 1;
}


// deleteFront()
// Deletes data at front of LL.
// Pre: !isEmpty(LL)
void deleteFront(List LL){
   Node N = NULL;
   if( LL==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(LL) ){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (index(LL) == 0) {
	   LL->index = -1;
   }
   N = LL->front;
   if( length(LL)>1 ) { 
      LL->front = LL->front->next; 
   }else{ 
      LL->front = LL->back = NULL; 
   }
   if (index(LL) > -1) {
	   LL->index -= 1;
   }
   LL->length--;
   freeNode(&N);
}

// deleteBack()
// Deletes data at back of LL
// Pre: !isEmpty(LL)
void deleteBack(List LL){
   Node node = NULL;
	if( LL==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(LL) ){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (index(LL) == length(LL) - 1) {
	   LL->index = -1;
   }
   node = LL->back;
   if (length(LL) > 1) {
	   LL->back = LL->back->prev;
       LL->back->next = NULL;
   }else{
	   LL->front = LL->back = NULL;
   }
   freeNode(&node);
   LL->length--;
}

// delete()
// deletes cursor element
void delete(List LL) {
   if( LL==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(LL) ){
      printf("List Error: calling delete() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (index(LL) == 0) {
	   deleteFront(LL);
	   return;
   }
   if (index(LL) == length(LL) - 1) {
	   deleteBack(LL);
	   return;
   }
   Node runner = LL->front;
	for (int i = 0; i < index(LL); i++) {
		runner = runner->next;
	}
	runner->prev->next = runner->next;
	runner->next->prev = runner->prev;
	freeNode(&runner);
    LL->index = -1;
    LL->length -= 1;
}



