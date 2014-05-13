#include "list.h"


void addToList( struct Node** list, unsigned char key, int value )
{
	struct Node* pNew = NULL;
	struct Node* pCurr = NULL;
	pNew = ( struct Node* )malloc( sizeof( struct Node ) );
	if ( pNew == NULL )
	{
		printf( "\nError malloc" );
		exit(-1);
	}
	if ( *list == NULL )
	{
		*list = pNew;
		pNew->item.value = value;
		pNew->item.key = key;
		pNew->pNext = NULL;
	}
	else
	{
		pNew->item.value = value;
		pNew->item.key = key;
		pNew->pNext = NULL;
		for ( pCurr = *list; pCurr->pNext != NULL; pCurr = pCurr->pNext )
		{}
		pCurr->pNext = pNew;
	}
}//end func

int countList( struct Node* list )
{
	struct Node* pCurr = list;
	int count = 0;
	while( pCurr->pNext != NULL )
	{
		count++;
		pCurr = pCurr->pNext;
	}
	count++;
	return count;
}//end func

void deleteList( struct Node* list )
{
	struct Node* pCurr = NULL;
	struct Node* pTemp = NULL;

	pCurr = list;
	while( pCurr != NULL )
	{
		pTemp = pCurr;
		pCurr = pCurr->pNext;
		free( pTemp );
	}

}//end func

void setItemList( struct Node** list, unsigned char key, int value )
{
	struct Node* pCurr = NULL;
	for ( pCurr = *list; pCurr != NULL; pCurr= pCurr->pNext )
	{
		if ( pCurr->item.key == key )
		{
			pCurr->item.value = value;
		}
	}

}//end func

int getItemList( struct Node* list, unsigned char key )
{
	struct Node* pCurr = NULL;
	int value = 0;
	for ( pCurr = list; pCurr != NULL; pCurr= pCurr->pNext )
	{
		if ( pCurr->item.key == key )
		{
			value = pCurr->item.value;
			return value;
		}
	}
	return value;
}//end func

int hasListKey( struct Node* list, unsigned char key )
{
	struct Node* pCurr = NULL;
	int result = 0;
	for ( pCurr = list; pCurr != NULL; pCurr= pCurr->pNext )
	{
		if ( pCurr->item.key == key )
		{
			result = 1;
		}
	}
	return result;
}//end func

void saveListToFileBin( struct Node* list,  FILE* pOutputFile )
{
	struct Node* pCurr = NULL;
	int count = countList( list );
	int countChar = 0;

	for ( pCurr = list; pCurr != NULL; pCurr = pCurr->pNext )
	{
		countChar += pCurr->item.value;
	}

	putw( countChar, pOutputFile );
	putw( count, pOutputFile );
	for ( pCurr = list; pCurr != NULL; pCurr = pCurr->pNext )
	{
		fputc( pCurr->item.key, pOutputFile );
		putw( pCurr->item.value, pOutputFile );
	}
}//end func

struct Node* loadListFromFileBin(  FILE* pInputFile, int* countChar )
{
	struct Node* list = NULL;
	char key;
	int value;
	int count;
	
	*countChar = getw( pInputFile );
	count = getw( pInputFile );
	while ( count > 0 )
	{
		key = fgetc( pInputFile );
		value = getw( pInputFile );
		addToList( &list, key, value );
		count--;
	}
	return list;
}//end func

