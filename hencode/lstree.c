#include "lstree.h"


void addToLsTree( struct ListNode** lsTree, struct TreeNode* node )
{
	struct ListNode* pNew = NULL;
	struct ListNode* pCurr = NULL;
	pNew = ( struct ListNode* )malloc( sizeof( struct ListNode ) );
	if ( pNew == NULL )
	{
		printf( "\nError malloc" );
		exit(-1);
	}
	if ( *lsTree == NULL )
	{
		*lsTree = pNew;
		pNew->node.value = node->value;
		pNew->node.pParent = node->pParent;
		pNew->node.pChild0 = node->pChild0;
		pNew->node.pChild1 = node->pChild1;
		pNew->node.key = node->key;
		pNew->pNext = NULL;
	}
	else
	{
		pNew->node.value = node->value;
		pNew->node.pParent = node->pParent;
		pNew->node.pChild0 = node->pChild0;
		pNew->node.pChild1 = node->pChild1;
		pNew->node.key = node->key;
		pNew->pNext = NULL;
		for ( pCurr = *lsTree; pCurr->pNext != NULL; pCurr = pCurr->pNext )
		{}
		pCurr->pNext = pNew;
	}
}//end func

void deleteLsTree( struct ListNode* lsTree )
{
	struct ListNode* pCurr;

	if ( lsTree == NULL ) return;
	pCurr = lsTree;
	if ( pCurr->node.pChild0 != NULL ) deleteLsTree( pCurr->node.pChild0 );
	if ( pCurr->node.pChild1 != NULL ) deleteLsTree( pCurr->node.pChild1 );
	free( pCurr );

}//end func

int countLsTree( struct ListNode* lsTree )
{
	struct ListNode* pCurr = lsTree;
	int count = 0;
	while( pCurr->pNext != NULL )
	{
		count++;
		pCurr = pCurr->pNext;
	}
	count++;
	return count;
}//end func

struct ListNode* extractMinFromLsTree( struct ListNode** lsTree )
{
	struct ListNode* pCurr = NULL;
	struct ListNode* pPrev = NULL;
	struct ListNode* pMin = *lsTree;
	int min = (*lsTree)->node.value;


	for ( pCurr= *lsTree; pCurr != NULL; pCurr = pCurr->pNext )
	{
		if ( min > pCurr->node.value )
		{
			min = pCurr->node.value;
			pMin = pCurr;
		}
	}

	for ( pCurr = *lsTree; pCurr != NULL && pCurr != pMin; 
			 pPrev = pCurr, pCurr = pCurr->pNext )
	{}

	if ( pCurr == NULL ) return NULL;
	
	if( pCurr == *lsTree ) //element is first
	{
		*lsTree = (*lsTree)->pNext;
	}
	else //element in the middle or last
	{
		pPrev->pNext = pCurr->pNext;
	}
	return pCurr;
}//end func

