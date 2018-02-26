
#include <stdio.h>
#include "fcyc2.h"
#define MAXELEMS 100

long data[MAXELEMS];


void test(int elems, int stride)
{
	long i, sx2 = stride * 2, sx3 = stride * 3, sx4 = stride * 4;
	long acc0 = 0, acc1 = 0, acc2 = 0, acc3 = 0;
	long length = elems;
	long limit = length - sx4;

	/*combine 4 elements at a time*/
	for (i = 0; i < limit; i++)
	{
		acc0 = acc0 + data[i];
		acc1 = acc1 + data[i + stride];
		acc2 = acc2 + data[i + sx2];
		acc3 = acc3 + data[i + sx3];
	}

	/*finish any remaining elements*/
	for (; i < length; i += stride)
	{
		acc0 = acc0 + data[i];
	}

	//return ((acc0 + acc1) + (acc2 + acc3));
}

double run(int size, int stride, double Mhz)
{
	double cycles;
	int elems = size / sizeof(double);

	test(elems, stride);
	cycles = fcyc2(test, elems, stride, 0);
	return (size / stride) / (cycles / Mhz);
}

int main()
{
	int size, stride;
	size = 1<<10;  //1<<10 to  1<<27
	stride = 2;    // 1 to 32
	double Mhz = 2500; // 2.5Ghz=2500Mhz
	double result=run(size, stride, Mhz);
	printf("%f \n",result);
    return 0;
}

