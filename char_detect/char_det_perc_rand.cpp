#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	srand(time(NULL));
	int n;
	FILE* out=fopen("rand_char_detect.plot", "w");
	fprintf(out, "1000 900 50000 3000 500 256\n\n");
	for(int i=0;i<900;i++)
	{
		for(int j=0;j<3000;j++)
		{
			fprintf(out,"%d ", (rand()%3-1));
		}
		fprintf(out,"\n");
	}
	fprintf(out,"\n");
	fprintf(out,"\n");
	for(int i=0;i<3000;i++)
	{
		for(int j=0; j<256;j++)
			fprintf(out,"%d ", 1);
		fprintf(out,"\n");
	}
	fprintf(out,"\n");
	fprintf(out,"\n");
	for(int i=0;i<3000;i++)
	{
			fprintf(out,"%d ", (rand()%100+10));
	}
	fprintf(out,"\n");
	fprintf(out,"\n");
	for(int i=0;i<256;i++)
	{
		fprintf(out,"%d ", rand()%1000+100);
	}

	fprintf(out,"\n");
	fclose(out);
}