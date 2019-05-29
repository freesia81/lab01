#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_SIZE   20
#define MAX_DATA_LENGTH 20

int main(int argc, char *argv[])
{
	char fNameList[MAX_DATA_SIZE][MAX_DATA_LENGTH] = { "abc.txt", "abce", "abcd.txt", "acde.txt"};
	int fNameCnt = 4;

	for(int i=0; i<fNameCnt; i++)
	{
		char buf[MAX_DATA_LENGTH] = {0, };
		char *ptr;

		// 확장자 제거
		memset(buf, 0x00, sizeof(buf));
		strcpy(buf, fNameList[i]);
		if ( (ptr = strchr(buf, '.')) != NULL )
			*ptr = 0x00;

		printf("%s\n", buf);
	}

	return 0;
}


