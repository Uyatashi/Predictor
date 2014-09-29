#include <string.h>

int checkhex(char* hex)
{
	for(int i = 0; i < strlen(hex); i++)
	{ if (!((hex[i] >= 48 && hex[i] <= 57) || (hex[i] >= 45 && hex[i] <= 70))) { return(0); }
	return(1);
}