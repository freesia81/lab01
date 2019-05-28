/*
 * util_fprintf.c
 *
 *  Created on: 2018. 7. 18.
 *      Author: ccomasora
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
	FILE *fp_out;

	fp_out = fopen("OUTPUT.TXT", "a+");
	if ( fp_out == NULL )
	{
		perror("file open error 1: ");
		exit(1);
	}

	for ( int i=0; i<10; i++ )
	{
		fprintf(fp_out, "%02d#%s\n", i, "AA");		/* 출력내용: 01#AA */
	}

	fclose(fp_out);

	return 0;
}
