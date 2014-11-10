#include <string.h>
#include <stdio.h>


extern FILE *input1, *out1, *out2, *out3, *res;
extern int mode, modebit1c;

void bit1w(int a, unsigned long temp);
void bit2w(int a, unsigned long temp);
void bit1cw(int a, unsigned long temp, unsigned long temp1);
int checkhex(char* hex);


long pc = 0;
long pc1 = 0;
long bit1hc = 0;
long bit2hc = 0;
long bit1chc = 0;
int prediction1c = 1;
float a, b, c;
/*typedef struct branch 
{
   unsigned long val;
   struct branch * next;
};

struct branch *head = NULL;
struct branch *curr = NULL; */

int parser(unsigned long *tempnum)
{
	int c;
	int i = 0;
	int counter = 0;
	char str[8];
	while ((c = fgetc(input1)) != 10)
	{ 
		if (counter > 8) { return(-2); }
		if ( c == -1 ) { return(0); }
		str[i] = c; 
		i++;
		counter++;
	}
	if (checkhex(str) == 0) { return(-1); }
	*tempnum = strtol(str, NULL, 16);
	return(1);
}

int checkhex(char* hex)
{
	int i;
	for( i = 0; i < 8; i++ ) { if (!((hex[i] >= 48 && hex[i] <= 57) || (hex[i] >= 65 && hex[i] <= 70))) { return(0); } }
	return(1);
}

/*struct branch* create_list(unsigned long val)
{
    printf("\n creating list with headnode as [%lu]\n",val);
    struct test_struct *ptr = (struct branch*)malloc(sizeof(struct branch));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->val = val;
    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}

struct test_struct* add_to_list(unsigned long val, bool add_to_end)
{
    if(NULL == head)
    {
        return (create_list(val));
    }

    if(add_to_end)
        printf("\n Adding node to end of list with value [%lu]\n",val);
    else
        printf("\n Adding node to beginning of list with value [%lu]\n",val);

    struct branch *ptr = (struct branch*)malloc(sizeof(struct branch));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->val = val;
    ptr->next = NULL;

    if(add_to_end)
    {
        curr->next = ptr;
        curr = ptr;
    }
    else
    {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}
struct branch* search_in_list(unsigned long val, struct branch **prev)
{
    struct branch *ptr = head;
    struct branch *tmp = NULL;
    int found = 0;

    printf("\n Searching the list for value [%lu] \n",val);

    while(ptr != NULL)
    {
        if(ptr->val == val)
        {
            found = true;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if(found == 1)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

int delete_from_list(unsigned long val)
{
    struct branch *prev = NULL;
    struct branch *del = NULL;

    printf("\n Deleting value [%d] from list\n",val);

    del = search_in_list(val,&prev);
    if(del == NULL)
    {
        return -1;
    }
    else
    {
        if(prev != NULL)
            prev->next = del->next;

        if(del == curr)
        {
            curr = prev;
        }
        else if(del == head)
        {
            head = del->next;
        }
    }

    free(del);
    del = NULL;

    return 0;
} */

void branchreport(int bcount, int icount) { printf("Branch : %d | Iterations : %d\n", bcount, icount); }

void initbit1() { out1 = fopen("1bitPredictionTable.txt", "w"); fprintf(out1,"1-bit Predictor\nAddress\t\tPrediction\tAction\n"); }

void initbit2() { out2 = fopen("2bitPredictionTable.txt", "w"); fprintf(out2,"2-bit Predictor\nAddress\t\tPrediction\tAction\n"); }

void initbit1c() { out3 = fopen("1bitCPredictionTable.txt", "w"); fprintf(out3, "(1,1) Correlating Predictor\nAddress\t\tPrediction\tAction\n"); }

int bit1(int pr, int s, unsigned long temp)
{
	pc++;
	if ((pr == 1) && (s == 1))	{ if (mode == 1) { bit1w(3, temp); } bit1hc++; return(1); }
	else if ((pr == 1) && (s == 0)) { if (mode == 1) { bit1w(2, temp); } return(0); }
	else if ((pr == 0) && (s == 1)) { if (mode == 1) { bit1w(1, temp); } return(1); }
	else { if (mode == 1) { bit1w(0, temp); } bit1hc++; return(0); }
}

int bit1c(int pr, int s, unsigned long temp, unsigned long temp1)
{
	pc1++;
	if ((pr == 1) && (s == 1))	{ if (mode == 1) { bit1cw(3, temp, temp1); } bit1chc++; return(1); }
	else if ((pr == 1) && (s == 0)) { if (mode == 1) { bit1cw(2, temp, temp1); } return(1); }
	else if ((pr == 0) && (s == 1)) { if (mode == 1) { bit1cw(1, temp, temp1); } return(1); }
	else { if (mode == 1) { bit1cw(0, temp, temp1); } bit1chc++; return(0); }
}
/*int bit1c(int pr, int s, unsigned long temp)
{
	if ((pr == 1) && (s == 1))	{ bit1w(3, temp); bit1hc++; return(1); }
	else if ((pr == 1) && (s == 0)) { bit1w(2, temp); return(0); }
	else if ((pr == 0) && (s == 1)) { bit1w(1, temp); return(1); }
	else { bit1w(0, temp); bit1hc++; return(0); }
}*/


void bit1w(int a, unsigned long temp)
{
	switch(a)
	{
		case 0:	{ fprintf(out1,"%lu\t\tNT\t\tNT (Hit)\n", temp); break; }
		case 1: { fprintf(out1,"%lu\t\tNT\t\tT\n", temp); break; }
		case 2: { fprintf(out1,"%lu\t\tT\t\tNT\n", temp); break; }
		case 3: { fprintf(out1,"%lu\t\tT\t\tT (Hit)\n", temp); }
	}
}

void bit1cw(int a, unsigned long temp, unsigned long temp1)
{
	//if (modebit1c == 1) { fprintf(out3,"%lu\t\tT\t\tT (Hit)\n", temp1); modebit1c = 0; }
	switch(a)
	{
		case 0:	{ fprintf(out3,"%lu\t\tNT\t\tNT (Hit)\n", temp); break; }
		case 1: { fprintf(out3,"%lu\t\tNT\t\tT\n", temp); break; }
		case 2: { fprintf(out3,"%lu\t\tT\t\tNT\n", temp); break; }
		case 3: { fprintf(out3,"%lu\t\tT\t\tT (Hit)\n", temp); }
	}
}
int bit2(int pr, int s, unsigned long temp)
{
	if ((pr == 0)  && (s == 0)) { if (mode == 1) { bit2w(0, temp); } bit2hc++; return(0); }
	else if ((pr == 0) && (s == 1)) { if (mode == 1) { bit2w(1, temp); } return(1); }
	else if ((pr == 1) && (s == 0)) { if (mode == 1) { bit2w(2, temp); } bit2hc++; return(0); }
	else if ((pr == 1) && (s == 1)) { if (mode == 1) { bit2w(3, temp); } return(2); }
	else if ((pr == 2) && (s == 0)) { if (mode == 1) { bit2w(4, temp); } return(1); }
	else if ((pr == 2) && (s == 1)) { if (mode == 1) { bit2w(5, temp); } bit2hc++; return(3); }
	else if ((pr == 3) && (s == 0)) { if (mode == 1) { bit2w(6, temp); } return(2); }
	else { if (mode == 1) { bit2w(7, temp); }bit2hc++; return(3); }
}

void bit2w(int a, unsigned long temp)
{
	switch(a)
	{
		case 0:	{ fprintf(out2,"%lu\t\tNT'\t\tNT (Hit)\n", temp); break; }
		case 1: { fprintf(out2,"%lu\t\tNT'\t\tT\n", temp); break; }
		case 2: { fprintf(out2,"%lu\t\tNT\t\tNT (Hit)\n", temp); break; }
		case 3: { fprintf(out2,"%lu\t\tNT\t\tT\n", temp); break; }
		case 4: { fprintf(out2,"%lu\t\tT\t\tNT\n", temp); break; }
		case 5: { fprintf(out2,"%lu\t\tT\t\tT (Hit)\n", temp); break; }
		case 6:	{ fprintf(out2,"%lu\t\tT'\t\tNT\n", temp); break; }
		case 7:	{ fprintf(out2,"%lu\t\tT'\t\tT (Hit)\n", temp); }
	}
}

void predictors(int *prediction1, int *prediction2, int state, unsigned long tempnum, unsigned long tempnum1, int mode)
{
	*prediction2 = bit2(*prediction2, state, tempnum);
	if (mode == 0) { *prediction1 = bit1(*prediction1, state, tempnum); }
	else { prediction1c = bit1c(prediction1c, state, tempnum, tempnum1); }
}

void resetpredictors(int *prediction1, int *prediction2)
{
	*prediction1 = 1;
	*prediction2 = 3;
}

void results(int mode)
{
	switch(mode)
	{
		case 1:
		{
			printf("Bit1 predictor accuracy : %00f\n", (100 *((float)bit1hc/pc)));
			printf("Bit2 predictor accuracy : %00f\n", (100 *((float)bit2hc/pc)));
			printf("Total accuracy :  %00f\n", (100 *((float)(bit1hc+bit2hc))/pc));
			break;
		}
		case 2:
		{
			res = fopen("Results.txt", "w");
			fprintf(res, "Bit1 predictor accuracy : %00.f\n", (100 *((float)bit1hc/pc)));
			fprintf(res, "Bit2 predictor accuracy : %00f\n", (100 *((float)bit2hc/pc)));
			fprintf(res, "Total accuracy :  %00f\n", (100 *((float)(bit1hc+bit2hc))/pc));
			fclose(res);
			printf("Bit1 predictor accuracy : %00f\n", (100 *((float)bit1hc/pc)));
			printf("Bit2 predictor accuracy : %00f\n", (100 *((float)bit2hc/pc)));
			printf("Total accuracy :  %00f\n", (100 *((float)(bit1hc+bit2hc))/pc));
			break;
		}
		default:
		{
			res = fopen("Results.txt", "w");
			a = 100 * (float)bit1hc/pc;
			b = 100 * (float)bit2hc/(pc1 + pc);
			c = 100 * (float)bit1chc/pc1;
			fprintf(res, "Bit1 predictor accuracy : %00.0f\n", a);
			fprintf(res, "Bit2 predictor accuracy : %00.0f\n", b);
			fprintf(res, "(1,1) correlating predictor accuracy : %00.0f\n", c);
			fprintf(res, "Total accuracy :  %00.0f\n", ((a+b+c)/3));
			fclose(res);
		}
	}
}