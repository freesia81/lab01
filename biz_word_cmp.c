#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int	main(int argc, char	*argv[]) {
	
	char strBase[1000] = {0, };
	char tmp[1000] = {0, };
	char ch1, ch2; 
	int nWordCnt = 0;
	
	strcpy(strBase, "1AA27CAAABB1");
	
	for(int i=0; i<strlen(strBase)+1; i++)
	{
		if ( i == 0)
		{
			ch1 = strBase[i];
			nWordCnt++;
			continue;
		}
		
		ch2 = strBase[i];
		
		if ( isupper(ch1) && isupper(ch2) && ch1 == ch2 )
		{
			nWordCnt++;
			continue;
		}
		
		if ( nWordCnt == 1 )
			sprintf(&tmp[strlen(tmp)], "%c", ch1);
		else if ( nWordCnt == 2 )
			sprintf(&tmp[strlen(tmp)], "%c%c", ch1, ch1);
		else
			sprintf(&tmp[strlen(tmp)], "%d%c", nWordCnt, ch1);
			
		ch1 = ch2;
		nWordCnt = 1;
	}
	
	printf("org: %s\n", strBase);
	printf("zip: %s\n", tmp);
	

	return 0;
}
