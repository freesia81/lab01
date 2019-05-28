#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "I am Studient";
	
	strupr(str);
	printf("%s\n", str);
	
	strlwr(str);
	printf("%s\n", str);
	
	return 0;
}