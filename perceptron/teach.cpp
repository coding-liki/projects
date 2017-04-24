#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

int main()
{
	Perceptron P1(500000,500000,500000);
	P1.Load("rand_1.plot");
	int A_num=P1.num_A;
	for(int k=0;k<10;k++)
	{
		FILE *in=fopen("vib.vib","r");
		int N;
		fscanf(in,"%d", &N);
		int *a=new int[A_num];
		int *b=new int[A_num];
		printf("N=%d\n", A_num);
		for(int i=0;i<N;i++)
		{
			printf("i=%d\n", i);
			for(int j=0;j<A_num;j++)
			{
				//printf("	1)j=%d\n", j);
				fscanf(in,"%d", &a[j]);
			}
			for(int j=0;j<A_num;j++)
			{
				//printf("	2)j=%d\n", j);
				fscanf(in,"%d", &b[j]);
			}
			P1.New_State(a);
			P1.Count();
			P1.learn(b);
		}
		P1.Save("perc.opt");
		fclose(in);
	}

}