#include <string.h>
#include <stdlib.h>

int checkhex(const char* hex)
{
	int i;
	for( i = 0; i < 8; i++ )
	{ 
		if (!((hex[i] >= 48 && hex[i] <= 57) || (hex[i] >= 65 && hex[i] <= 70))) { return(0); }
	}
	return(1);
}

void branchreport(int bcount, int icount) { printf("Branch : %d | Iterations : %d\n", bcount+1, icount); }


/*int bit1(int pr, int s)
{
	if ((pr == 1) && (s == 1))	{ bit1w(3); return(1); }
	else if ((pr == 1) && (s == 0)) { bit1w(2); return(0); }
	else if ((pr == 0) && (s == 1)) { bit1w(1); return(1); }
	else { 1bitpredictor(0); return(0); }
} */

//void bit1w(int a)
//{
	