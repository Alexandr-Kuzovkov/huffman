#include "lstree.h"

#define MAX_CODE_LEN 100

/**
* Huffman code table
**/
struct HuffCode
{
	unsigned char key;
	unsigned char code[MAX_CODE_LEN];
	unsigned char len;
};

struct HuffCodeRec
{
	struct HuffCode hcode;
	struct HuffCodeRec* pNext;
};

/**
* @param copy code1 to code 2 strings
* @param code1 string with code1
* @param code2 string with code2
**/
void copyCode( unsigned char* code1, unsigned char* code2 );

/**
* add new element to list with value 1 if key "ch" not exists or 
* increment value of element with key equals "ch" 
* @param list pointer to pointer to first element of list
* @param ch character
**/
void countChar( struct Node** list, char* buffer );

/**
* copy list to lsTree list
* @param list pointer to pointer to first element of list
* @param lsTree pointer to pointer to first element of list lsTree
**/
void list2lsTree( struct Node* list, struct ListNode** lsTree );

/**
* one step of Huffman tree create
* @param lsTree pointer to pointer to first element of list lsTree
**/
void createTree( struct ListNode** lsTree );

/**
* make Huffman code of character from Huffman tree
* @param node pointer to element of Huffman tree
* @return pointer to struct HuffCode
**/
struct HuffCode* makeHuffCode( struct ListNode* node );

/**
* reverse Huffman code
* @param code pointer to struct HuffCode
**/
void reverseHuffCode( struct HuffCode* code );

/**
* add new record to  Huffman code table
* @param table pointer to pointer to first element Huffman code table
* @param code pointer to struct HuffCode
**/
void addToHuffCodeTable( struct HuffCodeRec** table, struct HuffCode* code );

/**
* create  Huffman code table from Huffman tree
* @param table pointer to pointer to first element Huffman code table
* @param lsTree pointer to root element Huffman code tree
**/
void createHuffCodeTable( struct HuffCodeRec** table, struct ListNode* lsTree );

/**
* delete  Huffman code table
* @param table pointer  to first element Huffman code table
**/
void deleteHuffCodeTable( struct HuffCodeRec* table );

/**
* print  Huffman code table
* @param table pointer  to first element Huffman code table
**/
void printHuffCodeTable( struct HuffCodeRec* table );

/**
* encode character by Huffman code and write code to output file
* @param ch Character
* @param table pointer  to first element Huffman code table
* @param pOutputFile pointer to output file open in binary mode
**/
void charHuffEncode( unsigned char ch, struct HuffCodeRec* table, FILE* pOutputFile );

/**
* write to file code of last character
* @param pOutputFile pointer to output file open in binary mode
**/
void flushOutBuf( FILE* pOutputFile );

/**
* encode all character of string buffer by Huffman code and write code to output file
* @param buffer pointer to string buffer
* @param table pointer  to first element Huffman code table
* @param pOutputFile pointer to output file open in binary mode
**/
void stringHuffEncode( char* buffer, struct HuffCodeRec* table, FILE* pOutputFile );

/**
* decode character from Huffman code and write decoded characters to output file
* @param ch Character
* @param lsTree root element of Huffman tree
* @param pOutputFile pointer to output file open in binary mode
* @param maxNumberChar maximal length decoded files
**/
void charHuffDecode( unsigned char ch, struct ListNode* lsTree, FILE* pOutputFile, int maxNumberChar );

/**
* print progress current operation
* @param current Current value of count
* @param max Maximal value of count
* @param step Step print result
**/
void printProgress( int current, int max, int step );