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

	/* 구분자가 공백인 경우, 2가지 방법이 있슴
	 *   방법1) fscanf 사용시, 입력 프롬프트에 공백을 반드시 넣어준다.
	 *   방법2) strtok 사용시, 구분문자에 공백을 반드시 넣어준다.
	 *   Sample) 2018-07-11T12:00:02 KML 03
	 */

#if 1
	// 방법1 사용
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

	// 방법2 사용
	char buf_in[256] = {0, };

	while ( fgets(buf_in, sizeof(buf_in), fp_in) != NULL )
	{
		char *dtime = strtok(buf_in, " \r\n");	// 구분문자에 반드시 공백을 넣어준다.
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


