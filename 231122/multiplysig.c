#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void sendSig();
void killSig();

pid_t pid;
int i=1;
int j=1;
int isMulti = 0;

int main(){
        if((pid=fork())==0){
                i=1;
                j=1;
                signal(2,killSig);
                for(i;i<=20;){
                        isMulti=1;
                        for(j;j<=20;j++){
                                printf("%d * %d = %d\n",i,j,(i*j));
                        }
                        j=1;
                        i++;
                        isMulti=0;
                        sleep(1);
                }
        }
        else{
                signal(2,sendSig);
                while(1){
                        sleep(1);
                }
        }
}

void sendSig(int signo){
        kill(pid, signo);
}

void killSig(int signo){
        if(isMulti==1){
                printf("구구단 실행중이니 종료 불가\n");
        }
        else if(i>9){
                kill(-getpgrp(),SIGKILL);
        }
}