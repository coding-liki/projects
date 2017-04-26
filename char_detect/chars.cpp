#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int main()
{
	setlocale (LC_ALL, "rus");
	FILE* out=fopen("chars.ch", "w");
	FILE* in=fopen("jokl.ch","r");
	int a[400];
	char b;
	for(int i=0;i<154;i++)
	{
		fscanf(in,"%c", &b);
		a[b+128]=b;
	}
	fclose(in);
	const char alph[]="АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	for(int i=0;i<154;i++)
	{
		fprintf(out,"char[%c] number[%d] num1[%d]\n",a[i], a[i], a[i]+128);
	}
	char c;
	while(1)
	{
		scanf("%c", &c);
		printf("%c = %d and in nums %c = %d\n", c, c, a[c+128], c+128);
	}
	fclose(out);
}