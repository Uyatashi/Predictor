#include <string.h>
#include <stdio.h>


void bit1w(int a, FILE *temp);

int parser(char *str, FILE *in)
{
	int c;
	int i = 0;
	while ((c = fgetc(in)) != 10)
	{ 
		if ( c == -1 ) { return(0); }
		str[i] = c; 
		i++;
	}
	return(1);
}

int checkhex(char* hex)
{
	int i;
	for( i = 0; i < 8; i++ )
	{ 
		//printf("%c", hex[i]);
		if (!((hex[i] >= 48 && hex[i] <= 57) || (hex[i] >= 65 && hex[i] <= 70))) { return(0); }
	}
	return(1);
}

void branchreport(int bcount, int icount) { printf("Branch : %d | Iterations : %d\n", bcount, icount); }

void initbit1(FILE *temp) { fprintf(temp,"1-bit Predictor\nPrediction\tAction\n"); }

void initbit2(FILE *temp) { fprintf(temp,"2-bit Predictor\nPrediction\tAction\tPrediction\tAction\n"); }

int bit1(int pr, int s, FILE *temp)
{
	if ((pr == 1) && (s == 1))	{ bit1w(3, temp); return(1); }
	else if ((pr == 1) && (s == 0)) { bit1w(2, temp); return(0); }
	else if ((pr == 0) && (s == 1)) { bit1w(1, temp); return(1); }
	else { bit1w(0, temp); return(0); }
}

void bit1w(int a, FILE *temp)
{
	switch(a)
	{
		case 0:	{ fprintf(temp,"NT\t\tNT (Hit)\n"); break; }
		case 1: { fprintf(temp,"NT\t\tT\n"); break; }
		case 2: { fprintf(temp,"T\t\tNT\n"); break; }
		case 3: { fprintf(temp,"T\t\tT (Hit)\n"); }
	}
}