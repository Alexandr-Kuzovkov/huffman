#include <string.h>
#include "huff.h"

#define MAX_NUMBER_ARGS 4
#define FILENAME_LEN 255
#define PRINT_CODE "-print-symbol-codes"

/**
* return size of file 
* @param pFile pointer FILE* to open file
* @return size of file in bytes
**/
long fileSize( FILE* pFile );

/**
* open input and output files 
* @param argc number of command line arguments 
* @param argv[] array of  command line arguments
* @param files array of input and output files pointers
* @param needPrintCode pointer to flag needed print huffman code
* @return array of input and output files pointers
**/
FILE** openFiles( int argc, char* argv[], char** files, int* needPrintCode );