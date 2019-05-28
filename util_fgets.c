
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

	/* ���๮�ڷ� ���е� ���� �б�� fgets�� ����Ѵ�. �� �� newline�� ���ۿ� ���ԵǾ� ����ȴ�.
	 * �����ڰ� Ư�������� ���, strtok�� ����Ͽ� ���ڿ��� �Ľ��ϵ� "\r\n"�� �ݵ�� �߰������ �Ѵ�.
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
