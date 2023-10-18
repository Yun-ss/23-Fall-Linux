#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

pthread_mutex_t mtx;
double* pX;
double* pResult;
int terms;

void* TaskCode(void* argument) {
	int tid;
	tid = *((int*)argument);
	double value = pX[tid];
	double numer = pX[tid] * pX[tid] * pX[tid];
	double denom = 6.;
	int sign = -1;

	for (int j = 1; j < terms; j++) {
		value += (double)sign * numer / denom;
		numer *= pX[tid] * pX[tid];
		denom *= (2. * (double)j + 2.) * (2. * (double)j + 3.);
		sign *= -1;
	}
	pResult[tid] = value;
}
int main() {
	pthread_t threads[4];
	int args[4];
	int i;
	double x[4] = { 0,M_PI / 6.,M_PI / 3.,0.134 };
	double res[4];
	pX = x;
	pResult = res;
	terms=3;
	pthread_mutex_init(&mtx, NULL);
	for (i = 0; i < 4; ++i) {
		args[i] = i;
		pthread_create(&threads[i], NULL, TaskCode, (void*)&args[i]);
	}
	for (i = 0; i < 4; ++i) {
		pthread_join(threads[i], NULL);
	}
	for (i = 0; i < 4; i++) {
		printf("%lf\n", res[i]);
	}
	return 0;
}
