// Author : Antonios Papadopoulos
// Date :
// Course : Computer Architecture

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib1.h"


int main( int argc, char *argv[] )
{
	FILE *input1;
	char tempstr[9];
	int flag = 0;
	int state;
	int prediction1 = 1;
	int prediction2 = 1;
	int bc = 0;
	int ic = 0;
	int init = 0;
	long lid[2];
	unsigned long tempnum;
	if ( argc != 2 )
	{
		printf("Wrong number of arguments. Please re-run the program.\n");
		system("pause");
		return(1);
	}
	input1 = fopen(argv[1], "r");
	if (input1 == NULL) {perror("Error opening file\n"); return(2);}
	fopen("1bitPredictionTable.txt", "w");
	fopen("2bitPredictionTable.txt", "w");
	while(fgets(tempstr, 9,input1) != NULL)
	{
		puts(tempstr);
		/*if (checkhex(tempstr) == 0)
		{
				printf("Wrong address. Please provide a valid input file.\n");
				system("pause");
				return(-1);
		}*/
		tempnum = strtol(tempstr, NULL, 16);
		printf("%lu\n", tempnum);
		if (init == 1)
		{
			if (flag == 0)
			{
				if (tempnum == lid[0])
				{
					ic++;
					state = 1;
				}
				else
				{
					branchreport(bc, ic);
					lid[1] = tempnum;
					state = 0;
					bc++;
					flag++;
					ic = 1;
				}
			}
			else
			{
				if (tempnum == lid[1])
				{
					ic++;
					state = 1;
				}
				else if (tempnum == lid[0])
				{
					ic++;
					state = 0;
				}
				else
				{
					branchreport(bc, ic);
					bc++;
					lid[0] = tempnum;
					flag--;
					ic = 1;
					state = 0;
				}
			
			}
		}
		if (init == 0)
		{ 
			lid[0] = tempnum;
			init = 1;
			bc++;
			ic++;
		}
	//	prediction1 = bit1(prediction1, state);
	//	prediction2 = 2bit(prediction2, state);
	}
	fclose(input1);
	printf("Completed.");
	system("pause");
	return(0);
}