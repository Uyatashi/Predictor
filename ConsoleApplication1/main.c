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
	int state, flag1, flag2;
	int prediction1 = 1;
	int prediction2 = 3;
	int bc = 0;
	int ic[3], i;
	int init = 0;
	long lid[2];
	unsigned long tempnum;
	ic[0] = 0;
	ic[1] = 0;
	ic[2] = 0;
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
	while((flag2 = parser(tempstr, input1)) != 0)
	{
		if (flag2 == 1) {break;}
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
					prediction1 = bit1(prediction1, 1, out1, lid[0]);
					prediction2 = bit2(prediction2, 1, out2, lid[0]);
					ic[0]++;
					state = 1;
					continue;
				}
				else
				{
					lid[2] = tempnum;
					bc++;
					flag = 1;
					ic[2] = 1;
					continue;
				}
			}
			else
			{
					if (tempnum == lid[2])
					{
						if (flag1 == 1)
						{
							prediction1 = bit1(prediction1, 1, out1, lid[0]);
							prediction2 = bit2(prediction2, 1, out2, lid[0]);
							flag1 = 0;
							ic[1] = ic[2];
							ic[2] = 0;
						}	
						ic[2]++;
						continue;
					}
					else if (tempnum == lid[0])
					{
						ic[0]++;
						for (i = 1; i < ic[2]; i++)
						{
							prediction1 = bit1(prediction1, 1, out1, lid[2]);
							prediction2 = bit2(prediction2, 1, out2, lid[2]);
						}
						prediction1 = bit1(prediction1, 0, out1, lid[2]);
						prediction2 = bit2(prediction2, 0, out2, lid[2]);
						flag1 = 1;
						continue;
					}
					else
					{
						if (flag1 = 1)
						{
							prediction1 = bit1(prediction1, 0, out1, lid[0]);
							prediction2 = bit2(prediction2, 0, out2, lid[0]);
						}
						prediction1 = bit1(prediction1, 1, out1, tempnum);
						prediction2 = bit2(prediction2, 1, out2, tempnum);
						branchreport(bc-1, ic[0]);
						branchreport(bc, ic[2]+ic[1]);
						prediction1 = 1;
						prediction2 = 3;
						bc++;
						lid[0] = tempnum;
						flag = 0;
						ic[0] = 1;
						ic[1] = 0;
						ic[2] = 0;
						state = 0;
					}
			}	
		}
		if (init == 0)
		{ 
			lid[0] = tempnum;
			init = 1;
			bc++;
			ic[0]++;
			prediction1 = bit1(prediction1, 1, out1, lid[0]);
			prediction2 = bit2(prediction2, 1, out2, lid[0]);
			flag1 = 0;
		}
		
	}
	branchreport(bc, ic[0]);
	fclose(input1);
	fclose(out1);
	fclose(out2);
	//printf("Completed.");
	system("pause");
	return(0);
}