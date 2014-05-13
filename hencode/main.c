#include <sys\timeb.h>
#include "file.h"


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
	int fileLen = 0;
	int count = 0;
	int maxBlocks = 0;

	//open input and output files
	if ( ( pFiles = openFiles( argc, argv, files, &needPrintCode ) ) == NULL )
		return;
	pInputFile = pFiles[0];
	pOutputFile = pFiles[1];

	//fixed time begin and size of input file
	ftime( &timeStart );
	printf( "count chars..." );
	fileLen = fileSize( pInputFile );

	//count frequency chars
	while( ( ch = fgetc( pInputFile ) ) != EOF )
	{
		count++;
		countChar( &freqTable, ch );
		printProgress( count, fileLen, 20000 );
	}

	printf( "\ncreate tree..." );
	
	//build Huffman tree
	list2lsTree( freqTable, &lsTree );
	while ( countLsTree( lsTree ) > 1 ) createTree( &lsTree );
	
	//make Huffman code table
	printf( "\ncreate code table..." );
	createHuffCodeTable( &codeTable, lsTree );

	//print Huffman code table if need
	if ( needPrintCode == 1 )
	{
		printf( "\n---------------Code table----------------\n" );
		printHuffCodeTable( codeTable );
		printf( "\n-----------------------------------------\n" );
	}	

	//save to output file frequency table
	fileLen = saveListToFileBin( freqTable, pOutputFile );
	rewind( pInputFile );
	printf( "\nencode ... " );
	count = 0;
	
	//encode characters and write to output file
	while( ( ch = fgetc( pInputFile ) ) != EOF )
	{
		count++;
		charHuffEncode( (unsigned char)ch, codeTable, pOutputFile );
		printProgress( count, fileLen, 20000 );
	}
	flushOutBuf( pOutputFile );
	
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