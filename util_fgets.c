
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[])
{
	FILE *fp_in;
	char buf_in[255];

	fp_in = fopen("INPUT.TXT", "r");
	if ( fp_in == NULL )
	{
		perror("file open error 1: ");
		exit(1);
	}

	/* 개행문자로 구분된 파일 읽기는 fgets를 사용한다. 이 때 newline도 버퍼에 포함되어 저장된다.
	 * 구분자가 특수문자인 경우, strtok를 사용하여 문자열을 파싱하되 "\r\n"도 반드시 추가해줘야 한다.
	 * Sample) 2018-07-11T12:00:02#KML#03
	 */

	while ( fgets(buf_in, sizeof(buf_in), fp_in) != NULL )
	{
		char *dtime = strtok(buf_in, "#\r\n");
		char *type = strtok(NULL, "#\r\n");
		char *code = strtok(NULL, "#\r\n");

		printf("[(%ld)%s][(%ld)%s][(%ld)%s]\n",
				strlen(dtime), dtime,
				strlen(type), type,
				strlen(code), code);
	}

	fclose(fp_in);

	return 0;
}
