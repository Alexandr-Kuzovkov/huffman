#include "list.h"

/**
* element of linked list which may be elment of  huffman tree
**/
struct TreeNode
{
	int value;
	unsigned char key;
	struct ListNode* pParent;
	struct ListNode* pChild0;
	struct ListNode* pChild1;

};

struct ListNode
{
	struct TreeNode node;
	struct ListNode* pNext;
};

/**
* get number elements of list
* @param lsTree pointer to first element
* @return number of elements of list
**/
int countLsTree( struct ListNode* lsTree );

/**
* add new element to list
* @param lsTree pointer to pointer to first element
* @param node struct contained data of new element
**/
void addToLsTree( struct ListNode** lsTree, struct TreeNode* node ); 

/**
* remove element of list with min value and return her address
* @param list pointer to pointer to first element
* @return address of element
**/
struct ListNode* extractMinFromLsTree( struct ListNode** list );

/**
* delete list
* @param lsTree pointer to first element
**/
void deleteLsTree( struct ListNode* lsTree );
