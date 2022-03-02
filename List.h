//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
// Credits to Patrick Tantalo for initial List ADT
//-----------------------------------------------------------------------------
#ifndef QUEUE_H_INCLUDE_
#define QUEUE_H_INCLUDE_

#include<stdbool.h>
#include<stdio.h>


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList();

// freeList()
// Frees all heap memory associated with List *pLL, and sets *pLL to NULL.
void freeList(List* pLL);


// Access functions -----------------------------------------------------------

// index()
// Returns the index of the cursor
int index(List LL);

// get()
// Returns the cursor's element (data inside cursor)
void* get(List LL);

// front()
// Returns the value at the front of LL.
// Pre: !isEmpty(LL)
void* front(List LL);

// back()
// Returns the value at the back of LL.
// Pre: !isEmpty(LL)
void* back(List LL);

// length()
// Returns the length of LL.
int length(List LL);

// isEmpty()
// Returns true if LL is empty, otherwise returns false.
bool isEmpty(List LL);


// Manipulation procedures ----------------------------------------------------

// clear()
// Clears the List
void clear(List LL);

// set():
// Sets cursor's element's data
void set(List LL, void* x);

// moveFront()
// Moves cursor to the front
void moveFront(List LL);

// moveBack()
// Moves cursor to the back
void moveBack(List LL);

// moveNext()
// Moves cursor one step towards the end of list
void moveNext(List LL);

// movePrev()
// Moves cursor one step towards front of list
void movePrev(List LL);

// prepend()
// Places new data at the front of LL
void prepend(List LL, void* data);

// append()
// Places new data at the back of LL.
void append(List LL, void* data);

// deleteFront()
// Deletes data at front of LL.
void deleteFront(List LL);

// deleteBack()
// Deletes data at the back of LL
void deleteBack(List LL);

// delete()
// Deletes cursor element of LL
void delete(List LL);

// insertAfter()
// Inserts element after cursor
void insertAfter(List LL, void* x);

// insertBefore()
// Inserts element before cursor
void insertBefore(List LL, void* x);

// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of LL consisting of a space separated list 
// of ints to stdout.
void printList(FILE *out, List LL);

#endif

