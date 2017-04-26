#include "CImg.h"
using namespace cimg_library;

#include "perceptron.h"
int main() {
	Perceptron P1(50000,50000,50000);
	P1.Load("perc_char_det.opt");
	
	char t[255];
	unsigned char ans;
	for(int l=0;l<1;l++){
		FILE *in=fopen("vib_test.vib","r");
			int count;
			fscanf(in,"%d", &count);
		for(int c=0; c<count;c++){
			
			fscanf(in, "%s%c%c", &t, &ans,&ans);
			//printf("%s ans=(%d)\n", t, ans);
			CImg<unsigned char> image(t);
			
			image.resize(30,30);
			image.display("image");
			int *a=new int[900];
			int *b=new int[256];
			int o=0;
			for (CImg<unsigned char>::iterator it = image.begin(); it<image.end(); ++it) {
				//printf("%d ", *it);
				if(*it<=190)
				{
					a[o]=1;
				}
				else a[o]=0;
				o++;
			}
			
			P1.New_State(a);
			P1.Count();
			//P1.learn(b);
			printf("my answer is (%c)\n", (unsigned char)(P1.Get_One_C()));
		}
		fclose(in);
	}

	return 0;
}