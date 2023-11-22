#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void resetcount();
void timeup();

int main(){
        int password =1234;
        int input;
        signal(SIGINT,resetcount);
        signal(SIGALRM,timeup);
        alarm(10);
        while(1){
                scanf("%d",&input);
                if(password==input){
                        printf("Correct!\n");
                        exit(0);
                }
        }
}

void resetcount(int signo){
        alarm(10);
        printf("10 sec reset...\n");
}

void timeup(int signo){
        printf("Fire!\n");
        exit(0);
}