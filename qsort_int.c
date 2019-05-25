
#include <stdio.h>
#include <stdlib.h>

// 정수형 오름차순 정렬
int asc_compare(const void *a, const void *b)
{
	int num1 = *(int *)a;
	int num2 = *(int *)b;

	return num1 - num2;
}

// 정수형 내림차순 정렬
int desc_compare(const void *a, const void *b)
{
	int num1 = *(int *)a;
	int num2 = *(int *)b;

	return num2 - num1;
}

int main (int argc, char *argv[])
{
	int numArr[10] = { 8, 4, 2, 5, 3, 7, 10, 1, 6, 9 };

	// 오름차순 정렬
	qsort( numArr, sizeof(numArr)/sizeof(int), sizeof(int), asc_compare );

	for ( int i=0; i<10; i++ )
		printf("%d ", numArr[i]);
	printf("\n");


	// 내림차순 정렬
	qsort( numArr, sizeof(numArr)/sizeof(int), sizeof(int), desc_compare );

	for ( int i=0; i<10; i++ )
		printf("%d ", numArr[i]);
	printf("\n");

	return 0;
}
