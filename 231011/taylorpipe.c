#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define N 4
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAXLINE 100
void sinx_taylor(int num_elements, int terms, double* x, double* result){
	int n, length;
	int pid;
	int status;
	int fd[num_elements][2];
	char message[MAXLINE],line[MAXLINE];
	for(int i=0;i<num_elements;i++){
		pipe(fd[i]);
		int my_id=i;
		if((pid=fork())==0){
			close(fd[i][0]);
		
			double value = x[i];
			double number = x[i]*x[i]*x[i];
			double denom =6.; //3!
			int sign = -1;

			for(int j=1;j<terms;j++){
				value += (double)sign*number/denom;
				number *= x[i]*x[i];
				denom *= (2.*(double)j+2.)*(2.*(double)j+3.);
				sign *= -1;
			}
			sprintf(message,"%lf",value);
			length = strlen(message)+1;
			write(fd[i][1],message,length);
			exit(my_id);
		}
	}
	for(int i=0;i<num_elements;i++){
		wait(&status);
		int child_id= status >> 8;
		close(fd[child_id][1]);
		n=read(fd[child_id][0],line,MAXLINE);
		double value = atof(line);
		result[child_id]=value;
	}
}

int main(){
	double x[N] ={0,M_PI/6.,M_PI/3.,0.134};
	double res[N];

	sinx_taylor(N,3,x,res);
	for(int i=0;i<N;i++){
		printf("sin(%.2f) by Taylor series - %f\n",x[i], res[i]);
		printf("sin(%.2f)=%f\n",x[i],sin(x[i]));
	}
	return 0;
}
