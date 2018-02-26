// blocked.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ctime>

using namespace std;

#define MINBLOCK 8
#define MAXBLOCK 256
#define MINSIZE 512
#define MAXSIZE 4096

void mmm(double *a, double *b, double *c, int n, int B);
void mmmy(double *a, double *b, double *c, int n);

int main()
{
	for (int n = 512; n <= 512; n *= 2) {
		cout << "SIZE = " << n << endl;
		double *a, *b, *c;
		a = (double *)calloc(sizeof(double), n * n);
		b = (double *)calloc(sizeof(double), n * n);
		c = (double *)calloc(sizeof(double), n * n);
		memset(a, 0, n * n);
		memset(b, 0, n * n);
		for (int B = MINBLOCK; B <= MAXBLOCK; B *= 2) {
			cout << "  BLOCK = " << B << endl;
			double total_time = 0;
			clock_t start, end;
			for (int count = 0; count < 10; count++) {
				start = clock();
				mmm(a, b, c, n, B);
				//mmmy(a, b, c, n);
				end = clock();
				total_time += end - start;
			}

			cout << total_time / 10 << endl;
		}
	}

	system("pause");
	return 0;
}

/* Multiply n x n matrices a and b  */
void mmm(double *a, double *b, double *c, int n, int B) {
	int i, j, k;
	int i1, j1, k1;
	for (i = 0; i < n; i += B)
		for (j = 0; j < n; j += B)
			for (k = 0; k < n; k += B)
				/* B x B mini matrix multiplications */
				for (i1 = i; i1 < i + B; i1++)
					for (j1 = j; j1 < j + B; j1++)
						for (k1 = k; k1 < k + B; k1++)
							c[i1*n + j1] += a[i1*n + k1] * b[k1*n + j1];
}

void mmmy(double *a, double *b, double *c, int n)
{
	int i, j, k;     
	for (i = 0; i < n; i++)  
		for (j = 0; j < n; j++)             
			for (k = 0; k < n; k++)           
				c[i*n + j] += a[i*n + k] * b[k*n + j];
}
