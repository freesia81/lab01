#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char str[100];
	int  num;
} USER_TYPE;

/* 정수 오름차순 정렬 */
int asc_compare_int(const void *a, const void *b)
{
	int num1 = ((USER_TYPE *)a)->num;
	int num2 = ((USER_TYPE *)b)->num;

	return num1 - num2;
}

/* 정수 내림차순 정렬 */
int desc_compare_int(const void *a, const void *b)
{
	int num1 = ((USER_TYPE *)a)->num;
	int num2 = ((USER_TYPE *)b)->num;

	return num2 - num1;
}

/* 문자열 오름차순 정렬 */
int asc_compare_str(const void *a, const void *b)
{
	char *str1 = ((USER_TYPE *)a)->str;
	char *str2 = ((USER_TYPE *)b)->str;

	return strcmp(str1, str2);
}

/* 문자열 내림차순 정렬 */
int desc_compare_str(const void *a, const void *b)
{
	char *str1 = ((USER_TYPE *)a)->str;
	char *str2 = ((USER_TYPE *)b)->str;

	return strcmp(str2, str1);
}

// 문자열 + 정수형 오름차순 정렬
int asc_compare_str_int(const void *a, const void *b)
{
	char *str1 = ((USER_TYPE *)a)->str;
	char *str2 = ((USER_TYPE *)b)->str;

	int num1 = ((USER_TYPE *)a)->num;
	int num2 = ((USER_TYPE *)b)->num;

	if ( strcmp(str1, str2) != 0) 
		return strcmp(str1, str2);
	else 
		return num1 - num2;
}

// 구조체 출력함수
void PrintData(USER_TYPE *p, int cnt)
{
	for(int i=0; i<cnt; i++)
		printf("%s, %d\n", p[i].str, p[i].num);
	printf("\n");
}


int main(int argc, char *argv[])
{
	USER_TYPE data[4] = {{"AAA", 25}, {"JJJ", 5}, {"BBB", 40}, {"JJJ", 2}};

	// 문자열 오름차순 정렬
	qsort(data, sizeof(data)/sizeof(USER_TYPE), sizeof(USER_TYPE), asc_compare_str);
	PrintData(data, 4);

	// 정수 오름차순 정렬
	qsort(data, sizeof(data)/sizeof(USER_TYPE), sizeof(USER_TYPE), asc_compare_int);
	PrintData(data, 4);

	// 문자열 + 정수 오름차순 정렬
	qsort(data, sizeof(data)/sizeof(USER_TYPE), sizeof(USER_TYPE), asc_compare_str_int);
	PrintData(data, 4);

	return 0;

}
