#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	srand(time(NULL));
	int n;
	FILE* out=fopen("rand_1.plot", "w");
	fprintf(out, "500 9 500000 30000 500 9\n");
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<30000;j++)
		{
			fprintf(out,"%d ", (rand()%3-1));
		}
		fprintf(out,"\n");
	}
	fprintf(out,"\n");
	fprintf(out,"\n");
	for(int i=0;i<30000;i++)
	{
		for(int j=0; j<9;j++)
			fprintf(out,"%d ", 1);
		fprintf(out,"\n");
	}
	fprintf(out,"\n");
	fprintf(out,"\n");
	for(int i=0;i<30000;i++)
	{
			fprintf(out,"%d ", (rand()%12+3));
	}
	fprintf(out,"\n");
	fprintf(out,"\n");
	for(int i=0;i<9;i++)
	{
		fprintf(out,"%d ", rand()%24+31);
	}

	fprintf(out,"\n");
	fclose(out);
}