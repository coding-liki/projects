#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"
#include <time.h>
int Rand_Variants(int* a, int b)
{
	int *v;
	int c=0;
	for(int i=0;i<b; i++)
	{
		if(a[i]==1)c++;
	}
	v=new int[c];
	int d=0;
	for(int i=0;i<b; i++)
	{
		if(a[i]==1){
			v[d]=i;
			d++;
		}
	}
	if(c!=0){
		int fg=rand()%c;
		return v[fg];
	}
	else return -1;
}
int main()
{
	Perceptron P1(50000,50000,50000);
	P1.Load("perc.opt");
	int a[9];
	int b[9];
	int shag;
	int corb=0, cosb=0;
	srand(time(NULL));
	for(int i=0;i<9;i++) a[i]=1;
	while(1)
	{
		printf("поле\n");
		for(int i=0;i<9;i++)
		{
			printf("%d ", a[i]);
			if(i%3==2){
				printf("\n");
			}
		}
		while(1){
		printf("Ваш ход\n");
		scanf("%d", &shag);
		if(a[shag-1]==1)break;
		printf("Занято  ");
		}
		a[shag-1]=2;
		P1.New_State(a);
		P1.Count();

			printf("Состояние  --\n 	");
		for(int k=0;k<9;k++)
		{
			b[k]=P1.c_stats[k];
			printf("%d ",b[k] );
			if(k%3==2) printf("\n 	");
		}
		int klok=Rand_Variants(b,9);
		if(klok!=-1)
			a[Rand_Variants(b,9)]=-1;
		else
			printf("Хода нет\n");
		
	}

	printf("Hello_World\n");
}