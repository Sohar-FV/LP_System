#include <stdio.h>
#include <stdlib.h>
#include "ezsem.h"

const char* LOGF_TITLE_APPLI = "exo1";

/*
			P1		P2		P3
s1 c=0				P(s1)	P(s2)
s2 c=0		print   print   print
			V(s1)   V(s2)	
*/

void fils(int n)
{
	if (n==1) {
		printf("Je suis le processus %d\n", n);
		EZSEM_V(0);
	}

	if (n==2) {
		EZSEM_P(0);
		printf("Je suis le processus %d\n", n);
		EZSEM_V(1);
	}

	if (n==3) {
		EZSEM_P(1);
		printf("Je suis le processus %d\n", n);
	}
	fflush(stdout);
	exit(0);
}

int main() 
{
	FILE* f = NULL;
	int i, n;
	EZSEM_INIT(f, 0);
	EZSEM_INIT_COUNTER(0,0);
	EZSEM_INIT_COUNTER(1,0);

	for(i = 1; i <= 3; ++i)
	{
		if ((n=fork())==0)
		{
			fils(i);	
		}
	}
	EZSEM_END;
	printf("Terminé\n");
}
