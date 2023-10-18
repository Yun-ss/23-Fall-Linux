#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES

pthread_mutex_t mtx;
double *pX;
double *pResult;

void sinx_taylor(int num_elements,int terms, double* x, double* result){
	for(int i=0;i<num_elements;i++){
		double value =x[i];
		double numer =x[i] * x[i] * x[i];
		double denom =6.;
		int sign=-1;
		
		for(int j=1;j<terms;j++){
			value +=(double)sign * numer /denom;
			numer *= x[i] * x[i];
			denom *= (2.*(double)j+2.)*(2.*(double)j+3.);
			sign *= -1;
		}
		result[i] = value;
	}
}
void *TaskCode(void *argument){
	int tid;
	tid =*((int*)argument);
	double value = x[tid];



}
int main(){
	pthread_t thread[4];
	int args[4];
	int i;
	double x[4]={0,M_PI/6.,M_PI/3.,0.134};
	double res[4];
	pX = x;
	presult = res;
	pthread_mutex_init(&mtx,NULL);
	for(i=0;i<4;++i){
		args[i]=i;
		pthread_create(&threads[i],NULL,TaskCode,(void *)&args[i]);
	}
	for(i=0;i<4;++i){
		pthread_join(threads[i],NULL);
	}
	for(i=0;i<4;i++){
		printf("%d\n",res[i]);
	}
	return 0;

}
