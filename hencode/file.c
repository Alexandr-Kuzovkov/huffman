#include "file.h"

long fileSize( FILE* pFile )
{
	long size;
	long current = ftell( pFile );
	fseek( pFile, 0, SEEK_END );
	size = ftell( pFile );
	fseek( pFile, current, SEEK_SET );	
	return size;
}//end func

FILE** openFiles( int argc, char* argv[], char** files, int* needPrintCode )
{
	FILE* pInputFile = NULL;
	FILE* pOutputFile = NULL;
	FILE* pFiles[2];
	int i;
	int j = 0;
	
	//system( "cls" );

	if ( argc < 3 )
	{
		printf( "\nUsage: %s <input_file_name> <output_file_name>", argv[0] );
		return NULL;
	}
	else
	{
		for ( i = 1; i < argc && i < MAX_NUMBER_ARGS; i++ )
		{
			if ( argv[i][0] != '-' )
			{ 
				strcpy( files[j++], argv[i] );
			}
			else
			{
				if ( strcmp( argv[i], PRINT_CODE ) == 0 ) *needPrintCode = 1;
			}
		}
		
		if ( ( pInputFile = fopen( files[0], "rb" ) ) == NULL )
		{
			printf( "\nCan not open file %s", files[0] );
			return NULL;
		}

		if ( ( pOutputFile = fopen( files[1], "wb" ) ) == NULL )
		{
			printf( "\nCan not open file %s", files[1] );
			fclose( pInputFile );
			return NULL;
		}

		pFiles[0] = pInputFile;
		pFiles[1] = pOutputFile;
		return pFiles;
	}
}//end func