// Author : Antonios Papadopoulos
// Date :
// Course : Computer Architecture

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib1.h"

int main( int argc, char *argv[] )
{
	FILE *input1, *out1, *out2;
	char tempstr[8];
	int flag = 0;
	int state;
	int prediction1 = 1;
	int prediction2 = 3;
	int bc = 0;
	int ic[2];
	int init = 0;
	long lid[2];
	unsigned long tempnum;
	ic[0] = 0;
	ic[1] = 0;
	if ( argc != 2 )
	{
		printf("Wrong number of arguments. Please re-run the program.\n");
		system("pause");
		return(1);
	}
	input1 = fopen(argv[1], "r");
	if (input1 == NULL) {perror("Error opening file\n"); return(2);}
	out1 = fopen("1bitPredictionTable.txt", "w");
	out2 = fopen("2bitPredictionTable.txt", "w");
	initbit1(out1);
	initbit2(out2);
	while(parser(tempstr, input1) != 0)
	{
		if (checkhex(tempstr) == 0)
		{
				printf("Wrong address. Please provide a valid input file.\n");
				system("pause");
				return(-1);
		}
		tempnum = strtol(tempstr, NULL, 16);
		if (init == 1)
		{
			if (flag == 0)
			{
				if (tempnum == lid[0])
				{
					ic[0]++;
					state = 1;
				}
				else
				{
					lid[1] = tempnum;
					state = 0;
					bc++;
					flag++;
					ic[1] = 1;
				}
			}
			else
			{
				if (tempnum == lid[1])
				{
					ic[1]++;
					state = 1;
				}
				else if (tempnum == lid[0])
				{
					ic[0]++;
					state = 0;
				}
				else
				{
					branchreport(bc-1, ic[0]);
					branchreport(bc, ic[1]);
					bc++;
					lid[0] = tempnum;
					flag--;
					ic[0] = 1;
					ic[1] = 0;
					state = 0;
				}
			
			}
		prediction1 = bit1(prediction1, state, out1);
		//prediction2 = bit2(prediction2, state);
		}
		if (init == 0)
		{ 
			lid[0] = tempnum;
			init = 1;
			bc++;
			ic[0]++;
		}
		printf("%lu\n", tempnum);
		
	}
	fclose(input1);
	printf("Completed.");
	system("pause");
	return(0);
}