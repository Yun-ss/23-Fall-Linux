#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void wakeup();

int main(){
        signal(SIGALRM,wakeup);
        alarm(5);
        printf("loop...\n"); 
        while(1){
                sleep(1);
                printf("1 sec... \n");
        }
        printf("End of main\n");
}

void wakeup(int signo){
        printf("Wake up!");
}       