#include <stdio.h>
#include <stdlib.h>

/**
* element of linked list
**/

struct Item
{
	unsigned char key;
	int value;
};

struct Node
{
	struct Item item;
	struct Node* pNext;
};

/**
* get number elements of list
* @param list pointer to first element
* @return number elements of list
**/
int countList( struct Node* list );

/**
* add new element to list
* @param list pointer to pointer to first element of list
* @param key Key
* @param value value
**/
void addToList( struct Node** list, unsigned char key, int value );

/**
* delete list
* @param list pointer to first element of list
**/
void deleteList( struct Node* list );

/**
* set value element of list with given key
* @param list pointer to pointer to first element of list
* @param key Key
* @param value value
**/
void setItemList( struct Node** list, unsigned char key, int value );

/**
* get value element of list with given key
* @param list pointer to pointer to first element of list
* @param key Key
* @return value of element or NULL if false
**/
int getItemList( struct Node* list, unsigned char key );

/**
* get info about existsted element of list with given key
* @param list pointer to first element of list
* @param key Key
* @return 1 if element exists or 0 if false
**/
int hasListKey( struct Node* list, unsigned char key );

/**
* save list to file in binary mode
* @param list pointer to first element of list
* @param pOutputFile pointer to output file open in binary mode 
* @return summ of all elements values
**/
int saveListToFileBin( struct Node* list, FILE* pOutputFile );

/**
* load list from file in binary mode
* @param countChar summ of all elements values
* @param pInputFile pointer to input file open in binary mode 
* @return pointer to first element of list
**/
struct Node* loadListFromFileBin(  FILE* pInputFile, int* countChar );