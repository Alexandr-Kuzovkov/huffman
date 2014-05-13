#include "huff.h"

extern unsigned char outBuff = 0x0;
extern unsigned char currBit = 0x0;
extern unsigned char mask = 0x1;
extern unsigned char decodeMask = 0x80;
extern int currentChar = 0;
extern struct ListNode* pCurrTreeNode = NULL;


void countChar( struct Node** list, char* buffer )
{
	int count;
	char* pCh = buffer;
	while( *pCh != '\0' )
	{
		if ( hasListKey( *list, *pCh ) == 0 )
		{
			addToList( list, *pCh, 1 );
		}
		else
		{
			count = getItemList( *list, *pCh );
			count++;
			setItemList( list, *pCh, count );
		}
		pCh++;
	}
}//end func

void copyCode( unsigned char* code1, unsigned char* code2 )
{
	int i;
	for ( i = 0; i < MAX_CODE_LEN; i++ ) code1[i] = code2[i];
}//end func

void list2lsTree( struct Node* list, struct ListNode** lsTree )
{
	struct Node* pCurr = NULL;
	struct ListNode* pLsTree = NULL;
	struct TreeNode node;

	for ( pCurr = list; pCurr != NULL; pCurr = pCurr->pNext )
	{
		node.pChild0 = NULL;
		node.pChild1 = NULL;
		node.pParent = NULL;
		node.value = pCurr->item.value;
		node.key = pCurr->item.key;
		addToLsTree( lsTree, &node );
	}
}//end func

void createTree( struct ListNode** lsTree )
{
	struct ListNode* node0 = NULL ;
	struct ListNode* node1 = NULL;
	struct ListNode* pCurr = NULL;
	struct TreeNode* pNew = NULL;

	node0 = extractMinFromLsTree( lsTree );
	node1 = extractMinFromLsTree( lsTree );

	pNew = ( struct TreeNode* )malloc( sizeof( struct TreeNode ) );
	pNew->pChild0 = node1;
	pNew->pChild1 = node0;
	pNew->pParent = NULL;
	pNew->value = node0->node.value + node1->node.value;
	pNew->key = 0;
	addToLsTree( lsTree, pNew );
	for ( pCurr = *lsTree; pCurr->pNext != NULL; pCurr = pCurr->pNext )
	{}
	node0->node.pParent = pCurr;
	node1->node.pParent = pCurr;
	
}//end func


struct HuffCode* makeHuffCode( struct ListNode* node )
{
	unsigned char count = 0;
	struct ListNode* pCurr = NULL;
	struct HuffCode* pCode = NULL;
	pCode = ( struct HuffCode* )malloc( sizeof( struct HuffCode ) );
	for ( pCurr = node; pCurr != NULL; pCurr = pCurr->node.pParent )
	{
		if( pCurr->node.pParent == NULL ) continue; 
		if ( pCurr->node.pParent->node.pChild0 == pCurr ) 
		{
			pCode->code[count++] = 0;
		}
		else if ( pCurr->node.pParent->node.pChild1 == pCurr ) 
		{
			pCode->code[count++] = 1;
		}
	}
	pCode->len = count;
	pCode->key = 0;
	reverseHuffCode( pCode );
	return pCode;

}//end func

void reverseHuffCode( struct HuffCode* code )
{
	unsigned char i;
	unsigned char reverseCode[MAX_CODE_LEN];
	for ( i = 0; i < code->len; i++ )
	{
		reverseCode[i] = code->code[ code->len - i - 1 ]; 
	}
	for ( i = 0; i < code->len; i++ )
	{
		code->code[i] = reverseCode[i];
	}
}//end func

void addToHuffCodeTable( struct HuffCodeRec** table, struct HuffCode* code )
{
	struct HuffCodeRec* pNew = NULL;
	struct HuffCodeRec* pCurr = NULL;
	pNew = ( struct HuffCodeRec* )malloc( sizeof( struct HuffCodeRec ) );
	if ( pNew == NULL )
	{
		printf( "\nError malloc" );
		exit(-1);
	}
	if ( *table == NULL )
	{
		*table = pNew;
		pNew->hcode.key = code->key;
		pNew->hcode.len = code->len;
		copyCode( pNew->hcode.code, code->code );
		pNew->pNext = NULL;
	}
	else
	{
		pNew->hcode.key = code->key;
		pNew->hcode.len = code->len;
		copyCode( pNew->hcode.code, code->code );
		pNew->pNext = NULL;
	
		for ( pCurr = *table; pCurr->pNext != NULL; pCurr = pCurr->pNext )
		{}
		pCurr->pNext = pNew;
	}
}//end func

void createHuffCodeTable( struct HuffCodeRec** table, struct ListNode* lsTree )
{
	struct HuffCode* pCode = NULL;

	if ( lsTree != NULL )
	{
		if ( lsTree->node.pChild0 == NULL && lsTree->node.pChild1 == NULL )
		{
			pCode = makeHuffCode( lsTree );
			pCode->key = lsTree->node.key;
			addToHuffCodeTable( table, pCode );
			free( pCode );
		}
		
		if ( lsTree->node.pChild0 != NULL ) createHuffCodeTable( table, lsTree->node.pChild0 );
		if ( lsTree->node.pChild1 != NULL ) createHuffCodeTable( table, lsTree->node.pChild1 );
	}
}//end func

void deleteHuffCodeTable( struct HuffCodeRec* table )
{
	struct HuffCodeRec* pCurr = NULL;
	struct HuffCodeRec* pTemp = NULL;

	pCurr = table;
	while( pCurr != NULL )
	{
		pTemp = pCurr;
		pCurr = pCurr->pNext;
		free( pTemp );
	}
}//end func

void printHuffCodeTable( struct HuffCodeRec* table )
{
	struct HuffCodeRec* pCurr = NULL;
	unsigned char i;
	for ( pCurr = table; pCurr != NULL; pCurr = pCurr->pNext )
	{
		printf( "\n%c -> ", pCurr->hcode.key );
		for ( i = 0; i < pCurr->hcode.len; i++ ) putchar( pCurr->hcode.code[i] + 0x30 );
	}
}//end func

void charHuffEncode( unsigned char ch, struct HuffCodeRec* table, FILE* pOutputFile )
{
	struct HuffCodeRec* pCurr = NULL;
	unsigned char i;

	for ( pCurr = table; pCurr != NULL && pCurr->hcode.key != ch; pCurr = pCurr->pNext )
	{}
	if ( pCurr == NULL ) return;
	for ( i = 0; i < pCurr->hcode.len; i++ )
	{
		outBuff <<= 1;
		if ( pCurr->hcode.code[i] == 1 ) outBuff |= mask;
		currBit++;
		if ( currBit == 8 )
		{
			fputc( outBuff, pOutputFile );
			outBuff = 0;
			currBit = 0;
		}
	}
}//end func

void flushOutBuf( FILE* pOutputFile )
{
	if ( currBit == 0 ) return;
	outBuff <<= ( 8 - currBit );
	fputc( outBuff, pOutputFile );
}//end func

void stringHuffEncode( char* buffer, struct HuffCodeRec* table, FILE* pOutputFile )
{
	char* pCh = buffer;
	while( *pCh != '\0' )
	{
		charHuffEncode( *pCh, table, pOutputFile );
		pCh++;
	}
}//end func

void charHuffDecode( unsigned char ch, struct ListNode* lsTree, FILE* pOutputFile, int maxNumberChar )
{
	unsigned char i;

	if ( lsTree == NULL ) return;
	if ( pCurrTreeNode == NULL) pCurrTreeNode = lsTree; 
	if ( pCurrTreeNode->node.pChild0 == NULL && pCurrTreeNode->node.pChild1 == NULL )
	{
		fputc( pCurrTreeNode->node.key, pOutputFile );
		pCurrTreeNode = lsTree;
	}
	for ( i = 0; i < 8; i++ )
	{
		if( ( ch & decodeMask ) > 0 )
		{
			pCurrTreeNode = pCurrTreeNode->node.pChild1;
		}
		else
		{
			pCurrTreeNode = pCurrTreeNode->node.pChild0;
		}
		if ( pCurrTreeNode->node.pChild0 == NULL && pCurrTreeNode->node.pChild1 == NULL )
		{
			fputc( pCurrTreeNode->node.key, pOutputFile );
			pCurrTreeNode = lsTree;
			currentChar++;
			
			printProgress( currentChar, maxNumberChar, 20000);
		
			if ( currentChar >= maxNumberChar ) return;
		}
		ch <<= 1;
	}

}//end func

void printProgress( int current, int max, int step )
{
	int percent;

	if ( step == 0 || current > max ) return;
	if ( ( current % step ) == 0 )
	{
		percent = 100 / ( max / current );
		if ( current > step ) printf( "\b\b\b\b\b" );
		printf( "%3i %c", percent, '%' );
	}

}//end func