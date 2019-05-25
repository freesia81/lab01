
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 문자열 오름차순 정렬 */
int asc_compare(const void *a, const void *b)
{
	char *str1 = (char *)a;
	char *str2 = (char *)b;

	return strcmp(str1, str2);
}

/* 문자열 내림차순 정렬 */
int desc_compare(const void *a, const void *b)
{
	char *str1 = (char *)a;
	char *str2 = (char *)b;

	return strcmp(str2, str1);
}

int main (int argc, char *argv[])
{
	char strArr[5][100] = { "TEXT_B1", "TEXT_A3", "TEXT_A1", "TEXT_C11", "TEXT_B23" };

	// 오름차순 정렬
	qsort( strArr, 5, 100, asc_compare );

	for ( int i=0; i<5; i++ )
		printf("%s\n", strArr[i]);

	// 내림차순 정렬
	qsort( strArr, 5, 100, desc_compare );

	for ( int i=0; i<5; i++ )
		printf("%s\n", strArr[i]);
		
	return 0;
}
