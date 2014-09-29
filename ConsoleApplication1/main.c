// Author : Antonios Papadopoulos
// Date :
// Course : Computer Architecture

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int checkhex(char* hex)
{
	int i;
	for(i = 0; i < strlen(hex); i++)
	{ if (!((hex[i] >= 48 && hex[i] <= 57) || (hex[i] >= 45 && hex[i] <= 70))) { return(0); }
	return(1);
}

int main( int argc, char *argv[] )
{
	FILE *input1;
	char tempstr [9];
	int flag = 1;
	int state;
	int bc = 0;
	int init = 1;
	long lid[2];
	unsigned long tempnum;
	if ( argc != 2 )
	{
		printf("Wrong number of arguments. Please re-run the program.\n");
		return(1);
	}
	input1 = fopen(argv[1], "r");
	if (input1 == NULL) {perror("Error opening file\n"); return(2);}
	while(fgets(tempstr, 9,input1) != NULL)
	{
		if (checkhex(tempstr) == 0)
		{
			printf("Wrong address. Please provide a valid input file.\n");
			return(-1);
		}
		puts(tempstr);
		tempnum = strtol(tempstr, NULL, 16);
		printf("%lu", tempnum);
		/*if (init = 1)
		{
			lid[0] = tempnum;
			init = 0;
			bc++
		}
		else
		{
			lid[1] = tempnum;
		}*/
	}
	fclose(input1);
	printf("Completed.");
	system("pause");
	return(0);
}