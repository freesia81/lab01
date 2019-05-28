/*
 * util_fscanf.c
 *
 *  Created on: 2018. 7. 18.
 *      Author: ccomasora
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
	FILE *fp_in;

	fp_in = fopen("INPUT.TXT", "r");
	if ( fp_in == NULL )
	{
		perror("file open error 1: ");
		exit(1);
	}

	/* �����ڰ� ������ ���, 2���� ����� �ֽ�
	 *   ���1) fscanf ����, �Է� ������Ʈ�� ������ �ݵ�� �־��ش�.
	 *   ���2) strtok ����, ���й��ڿ� ������ �ݵ�� �־��ش�.
	 *   Sample) 2018-07-11T12:00:02 KML 03
	 */

#if 1
	// ���1 ���
	char dtime[100] = {0, };
	char type[100] = {0, };
	int code = 0;

	while ( fscanf(fp_in, "%s %s %d", dtime, type, &code) != EOF )
	{
		printf("[(%ld)%s][(%ld)%s][%d]\n",
				strlen(dtime), dtime,
				strlen(type), type,
				code);
	}

#else

	// ���2 ���
	char buf_in[256] = {0, };

	while ( fgets(buf_in, sizeof(buf_in), fp_in) != NULL )
	{
		char *dtime = strtok(buf_in, " \r\n");	// ���й��ڿ� �ݵ�� ������ �־��ش�.
		char *type = strtok(NULL, " \r\n");
		char *code = strtok(NULL, " \r\n");

		printf("[(%ld)%s][(%ld)%s][(%ld)%s]\n",
				strlen(dtime), dtime,
				strlen(type), type,
				strlen(code), code);
	}
#endif

	fclose(fp_in);

	return 0;
}


