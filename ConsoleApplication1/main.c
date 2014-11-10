// Author : Antonios Papadopoulos
// Date :
// Course : Computer Architecture

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib1.h"

FILE *input1, *out1, *out2, *out3, *res;
int mode;
int modebit1c = 0;

int main( int argc, char *argv[] )
{
	int flag, flag1, flag2, flag3;
	int prediction1, prediction2, predictionInner1, predictionInner2;
	int bc, i;
	int ic[3];
	int init = 0;
	unsigned long lid[2];
	unsigned long tempnum;
	if ( argc != 2 )
	{
		printf("Wrong number of arguments. Please re-run the program.\n");
		system("pause");
		return(1);
	}
	input1 = fopen(argv[1], "r");
	printf("Please enter the mode : ");
	scanf("%d", &mode);
	if (input1 == NULL) {perror("Error opening file\n"); return(2);}
	if (mode == 1)
	{
		initbit1();
		initbit2();
		initbit1c();
	}
	while(1)
	{
		flag2 = parser(&tempnum);
	//	printf("%lu\n", tempnum);
		if (flag2 == 0)
		{
		//	printf("vrika EOF\n");
			predictors(&prediction1, &prediction2, 0, tempnum, lid[0], 0);
			break; 
		}
		switch(flag2)
		{
			case(-1):
			{
				printf("Wrong address(Comments). Please provide a valid input file.\n");
				return(-1);
			}
			case(-2):
			{
				printf("Wrong address(invalid character). Please provide a valid input file.\n");
				return(-1);
			}
		}
		switch(init)
		{
			case 1:
			{  
				switch(flag)
				{
					case 0:
					{
						if (tempnum == lid[0])
					   	{
							predictors(&prediction1, &prediction2, 1, tempnum, lid[0], 0);// pc++;
						//	printf("Idio\n %d", pc);
						//	system("pause");
							ic[0]++;
							flag3 = 1;
						}
						else if (flag3 == 0)
						{
							predictors(&prediction1, &prediction2, 1, lid[0], lid[0], 1);// pc++;
						//	printf("Prwth fora diaforetiko\n %d", pc);
						//	system("pause");
							lid[2] = tempnum;
							ic[1] = 0;
							ic[2] = 1;
							bc++;
							flag = 1;
							modebit1c = 1;
						}
						else
						{
						//	branchreport(bc, ic[0]);
							predictors(&prediction1, &prediction2, 0, lid[0], lid[0], 0);// pc++;
							resetpredictors(&prediction1, &prediction2);
							lid[0] = tempnum;
							bc++;
							ic[0] = 1;
							flag3 = 0;
				//			printf("Prwth fora diaforetiko (mesa)\n %d", pc);
				//			system("pause");
						}
						break;
					}
					default: //flag == 1
					{
						if (tempnum == lid[2])
						{
							if (flag1 == 1)
							{
								predictors(&prediction1, &prediction2, 1, lid[0], lid[0], 1);// pc++;
								flag1 = 0;
							}
							ic[2]++;
					//		printf("Epanalamvanetai sto inner loop.\n %d", pc);
					//		system("pause");
						}
						else if (tempnum == lid[0])
						{
							modebit1c = 1;
							for(i = 1; i < ic[2]; i++)
							{
								predictors(&predictionInner1, &predictionInner2, 1, lid[2], lid[0], 1); //pc++;
							}
							predictors(&predictionInner1, &predictionInner2, 1, lid[2], lid[0], 1);
							ic[0]++;
							ic[1] += ic[2];
							ic[2] = 0;
							flag1 = 1;
					//		printf("Gyrnaei sto outer loop.\n %d", pc);
					//		system("pause");
						}
						else
						{
					//		branchreport(bc-1, ic[0]);
					//		branchreport(bc, ic[1]);
							predictors(&prediction1, &prediction2, 0, lid[0], lid[0], 1); //pc++;
							resetpredictors(&prediction1, &prediction2);
							resetpredictors(&predictionInner1, &predictionInner2);
							lid[0] = tempnum;
							bc++;
							ic[0] = 1;
							flag = 0;
							flag3 = 0;
					//		printf("Vrike kainourgio loop\n %d", pc);
					//		system("pause");
						}
					}
				}
				break;
			}
			default: // init = 0
			{
				lid[0] = tempnum;
				ic[0] = 1;
				prediction1 = 1;
				prediction2 = 3;
				predictionInner1 = 1;
				predictionInner2 = 3;
				//	printf("%d %d", prediction1, prediction2);
				init = 1;
				bc = 1;
				ic[0] = 0;
				ic[1] = 0;
				ic[2] = 0;
				flag = 0;
				flag1 = 0;
				flag3 = 0;
			//	printf("Prwth dieythynsh\n");
			//	system("pause");
			}
					/*	switch(init)
		{
			case 1:
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
						prediction1 = bit1(prediction1, 1, out1, lid[2]);
						prediction2 = bit2(prediction2, 1, out2, lid[2]);
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
		case 0:
		{ 
		/*	branch *head = NULL;
			branch *temp;
			temp = (branch *)malloc(sizeof(branch));
			temp = head;
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			branch *temp1;
			temp1 = (branch *)malloc(sizeof(branch));
			temp1->val = tempnum;
			temp1->next = NULL;
			temp->next = temp1;
			tempnum = 
			init = 1;
			bc++;
			ic[0] = 1;
			prediction1 = bit1(prediction1, 1, out1, tempnum);
			prediction2 = bit2(prediction2, 1, out2, tempnum);
			flag1 = 0;
		} */
		}
	}
	fclose(input1);
	if (mode == 1)
	{
		fclose(out1);
		fclose(out2);
		fclose(out3);
	}
	results(0);
	system("pause");
	return(0);
}