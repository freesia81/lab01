#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char str[100];
	int  num;
} USER_TYPE;

/* ������ �������� ���� */
int asc_compare_int(const void *a, const void *b)
{
	int num1 = ((USER_TYPE *)a)->num;
	int num2 = ((USER_TYPE *)b)->num;

	return num1 - num2;
}

/* ������ �������� ���� */
int desc_compare_int(const void *a, const void *b)
{
	int num1 = ((USER_TYPE *)a)->num;
	int num2 = ((USER_TYPE *)b)->num;

	return num2 - num1;
}

/* ���ڿ� �������� ���� */
int asc_compare_str(const void *a, const void *b)
{
	char *str1 = ((USER_TYPE *)a)->str;
	char *str2 = ((USER_TYPE *)b)->str;

	return strcmp(str1, str2);
}

/* ���ڿ� �������� ���� */
int desc_compare_str(const void *a, const void *b)
{
	char *str1 = ((USER_TYPE *)a)->str;
	char *str2 = ((USER_TYPE *)b)->str;

	return strcmp(str2, str1);
}


void PrintData(USER_TYPE *p, int cnt)
{
	for(int i=0; i<cnt; i++)
		printf("%s, %d\n", p[i].str, p[i].num);
	printf("\n");
}


int main(int argc, char *argv[])
{
	USER_TYPE data[3] = {{"Ami", 25}, {"Jason",   5}, {"Babi",    40}};

	// ������ �������� ����
	qsort(data, sizeof(data)/sizeof(USER_TYPE), sizeof(USER_TYPE), asc_compare_int);
	PrintData(data, 3);

	// ������ �������� ����
	qsort(data, sizeof(data)/sizeof(USER_TYPE), sizeof(USER_TYPE), desc_compare_int);
	PrintData(data, 3);

	// ���ڿ� �������� ����
	qsort(data, sizeof(data)/sizeof(USER_TYPE), sizeof(USER_TYPE), asc_compare_str);
	PrintData(data, 3);

	// ���ڿ� �������� ����
	qsort(data, sizeof(data)/sizeof(USER_TYPE), sizeof(USER_TYPE), desc_compare_str);
	PrintData(data, 3);

	return 0;

}
