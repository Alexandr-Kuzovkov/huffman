#include <sys\timeb.h>
#include "file.h"

#define PRINT_CODE "-print-symbol-codes"
#define MAX_NUMBER_ARGS 4
#define FILENAME_LEN 255

void main( int argc, char* argv[] )
{
	FILE* pInputFile = NULL;
	FILE* pOutputFile = NULL;
	FILE** pFiles = NULL;
	struct Node* freqTable = NULL;
	struct ListNode* lsTree = NULL;
	struct HuffCodeRec* codeTable = NULL;
	int ch;
	struct timeb timeStart;
	struct timeb timeEnd;
	long timeExec;
	char inputFile[FILENAME_LEN];
	char outputFile[FILENAME_LEN];
	char* files[] = { 
						inputFile, 
						outputFile
					};
	int needPrintCode = 0;
	int maxNumberChar = 0;

	//open input and output files
	if ( ( pFiles = openFiles( argc, argv, files, &needPrintCode ) ) == NULL )
		return;
	pInputFile = pFiles[0];
	pOutputFile = pFiles[1];
	
	//fixed begin time
	ftime( &timeStart );

	//load frequency table from input file
	printf( "load frequency table..." );
	freqTable = loadListFromFileBin( pInputFile, &maxNumberChar );
	printf( "\ncreate tree..." );
	
	//build Huffman code tree
	list2lsTree( freqTable, &lsTree );
	while ( countLsTree( lsTree ) > 1 ) createTree( &lsTree );

	//decode data of input file and write decoded characters to output file
	printf( "\ndecode..." );
	while( ( ch = fgetc( pInputFile ) ) != EOF )
	{
		charHuffDecode( (unsigned char)ch, lsTree, pOutputFile, maxNumberChar );
	}
	
	//print Huffman code table if need
	if ( needPrintCode == 1 )
	{
		printf( "\n---------------Code table----------------\n" );
		createHuffCodeTable( &codeTable, lsTree );
		printHuffCodeTable( codeTable );
		printf( "\n-----------------------------------------\n" );
	}

	//fixed end time
	ftime( &timeEnd );

	//computing execute time
	timeExec = ( timeEnd.time - timeStart.time ) * 1000 + timeEnd.millitm - timeStart.millitm;

	//print results
	printf( "\nSize of input file %s is %d bytes", files[0], fileSize( pInputFile ) );
	printf( "\nSize of output file %s is %d bytes", files[1], fileSize( pOutputFile ) );
	printf( "\nUnique characters: %d", countList( freqTable ) );
	printf( "\nTime of execution: %d milliseconds", timeExec );
	
	//clear memory and close files
	deleteList( freqTable );
	deleteLsTree( lsTree );
	deleteHuffCodeTable( codeTable );
	fclose( pInputFile );
	fclose( pOutputFile );
	printf( "\nDone" );

}