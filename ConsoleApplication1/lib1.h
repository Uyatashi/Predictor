#include <string.h>
#include <stdio.h>


void bit1w(int a, FILE *temp);
void bit2w(int a, FILE *temp);

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
	for( i = 0; i < 8; i++ ) { if (!((hex[i] >= 48 && hex[i] <= 57) || (hex[i] >= 65 && hex[i] <= 70))) { return(0); } }
	return(1);
}

void branchreport(int bcount, int icount) { printf("Branch : %d | Iterations : %d\n", bcount, icount); }

void initbit1(FILE *temp) { fprintf(temp,"1-bit Predictor\nPrediction\tAction\n"); }

void initbit2(FILE *temp) { fprintf(temp,"2-bit Predictor\nPrediction\tAction\tPrediction\tAction\n"); }

int bit1(int pr, int s, FILE *temp, long lid)
{
	if ((pr == 1) && (s == 1))	{ bit1w(3, temp, lid); return(1); }
	else if ((pr == 1) && (s == 0)) { bit1w(2, temp, lid); return(0); }
	else if ((pr == 0) && (s == 1)) { bit1w(1, temp, lid); return(1); }
	else { bit1w(0, temp, lid); return(0); }
}

void bit1w(int a, FILE *temp, long lid)
{
	switch(a)
	{
		case 0:	{ fprintf(temp,"%lu\t\tNT\t\tNT (Hit)\n", lid); break; }
		case 1: { fprintf(temp,"%lu\t\tNT\t\tT\n", lid); break; }
		case 2: { fprintf(temp,"%lu\t\tT\t\tNT\n", lid); break; }
		case 3: { fprintf(temp,"%lu\t\tT\t\tT (Hit)\n", lid); }
	}
}

int bit2(int pr, int s, FILE *temp, long lid)
{
	if ((pr == 0)  && (s == 0)) { bit2w(0, temp, lid); return(0); }
	else if ((pr == 0) && (s == 1)) { bit2w(1, temp, lid); return(1); }
	else if ((pr == 1) && (s == 0)) { bit2w(2, temp, lid); return(0); }
	else if ((pr == 1) && (s == 1)) { bit2w(3, temp, lid); return(2); }
	else if ((pr == 2) && (s == 0)) { bit2w(4, temp, lid); return(1); }
	else if ((pr == 2) && (s == 1)) { bit2w(5, temp, lid); return(3); }
	else if ((pr == 3) && (s == 0)) { bit2w(6, temp, lid); return(2); }
	else { bit2w(7, temp, lid); return(3); }
}

void bit2w(int a, FILE *temp, long lid)
{
	switch(a)
	{
		case 0:	{ fprintf(temp,"%lu\t\tNT'\t\tNT (Hit)\n", lid); break; }
		case 1: { fprintf(temp,"%lu\t\tNT'\t\tT\n", lid); break; }
		case 2: { fprintf(temp,"%lu\t\tNT\t\tNT (Hit)\n", lid); break; }
		case 3: { fprintf(temp,"%lu\t\tNT\t\tT\n", lid); break; }
		case 4: { fprintf(temp,"%lu\t\tT\t\tNT\n", lid); break; }
		case 5: { fprintf(temp,"%lu\t\tT\t\tT (Hit)\n", lid); break; }
		case 6:	{ fprintf(temp,"%lu\t\tT'\t\tNT\n", lid); break; }
		case 7:	{ fprintf(temp,"%lu\t\tT'\t\tT (Hit)\n", lid); }
	}
}