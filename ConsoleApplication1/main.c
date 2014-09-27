// Author : Antonios Papadopoulos
// Date :
// Course : Computer Architecture

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int main( int argc, char *argv[] )
{
	FILE *input1;
	char tempstr [9];
	int flag = 1;
	int state;
	int bc = 0;
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
		puts(tempstr);
		tempnum = strtol(tempstr, NULL, 16);
		printf("%lu", tempnum);
	}
	fclose(input1);
	printf("Completed.");
	system("pause");
	return(0);
}