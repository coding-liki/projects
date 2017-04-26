#include "CImg.h"
using namespace cimg_library;

#include "perceptron.h"
int main() {
	Perceptron P1(50000,50000,50000);
	P1.Load("rand_char_detect.plot");
	
	char t[255];
	unsigned char ans;
	for(int l=0;l<10;l++){
		FILE *in=fopen("vib.vib","r");
			int count;
			fscanf(in,"%d", &count);
		for(int c=0; c<count;c++){
			
			fscanf(in, "%s%c%c", &t, &ans,&ans);
			printf("\n\n%s ans=(%d)\n", t, ans);
			CImg<unsigned char> image(t);
			
			image.resize(30,30);
			int *a=new int[900];
			int *b=new int[256];
			int o=0;
			for (CImg<unsigned char>::iterator it = image.begin(); it<image.end(); ++it) {
				//printf("%d ", *it);
				if(*it<=100)
				{
					a[o]=1;
				}
				else a[o]=0;
				o++;
			}
			for(int i=0;i<256;i++)
			{
				if(i==ans)
					b[i]=1;
				else
					b[i]=0;
			}
			printf("\n");
			P1.New_State(a);
			P1.Count();
			P1.learn(b);
			printf("char is (%d)\n", P1.Get_One_C());
			for(int i=0;i<256;i++)
			{
				if(i==ans)
					b[i]=1;
				else
					b[i]=0;
				//printf("%d is %d", b[i], P1.c_stats[i]);
			}
		}
		fclose(in);
	}
	P1.Save("perc_char_det.opt");

	return 0;
}