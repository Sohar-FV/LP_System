#include <stdio.h>
#include <stdlib.h>
#include "ezsem.h"

const char* LOGF_TITLE_APPLI = "exo1";

/*
			Pi

s1 c=2		think
			P(s1)
			eat
			V(s1)
			think
*/

void fils(int n)
{
		
	EZSEM_P(0);
	printf("Je mange %d\n", n);
	EZSEM_V(0);

	fflush(stdout);
	exit(0);
}

int main() 
{
	FILE* f = NULL;
	int i, n;
	EZSEM_INIT(f, 0);
	EZSEM_INIT_COUNTER(0,0);

	for(i = 1; i <= 5; ++i)
	{
		if ((n=fork())==0)
		{
			fils(i);	
		}
	}
	EZSEM_END;
	printf("Terminé\n");
}
