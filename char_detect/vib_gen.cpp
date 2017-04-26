#include "CImg.h"
using namespace cimg_library;

int main()
{
	CImg<unsigned char> image(500,400,1,3,255);
	 CImgList<unsigned char> f=CImg<unsigned char>::font(12);
	 image.display("hi");
}