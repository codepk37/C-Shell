#include "header.h"
//Perfect done  
//works good ,i think completed  ->work on spec13
/*
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>*/
int getnum(char*p){
    int c=0;
    char st[strlen(p)+1];
    for(int i=0;i<strlen(p);i++){
        if(p[i]<='9' && p[i]>='0'){
            st[c]=p[i];
            c++;
        }
        
    }
    return atoi(st);
    
}

// Function to bring a process to the foreground
void foreground(pid_t pid) {
    if (kill(pid, SIGCONT) == -1) { //bg code
        perror("kill");
        printf("No such process found\n");
    }                               //bg code
    
    int status;
    waitpid(pid, &status, WUNTRACED); 
}

// Function to change the state of a stopped process to running (background)
void background(pid_t pid) {
    if (kill(pid, SIGCONT) == -1) {// resume stopped or paused processes.
        perror("kill");
        printf("No such process found\n");
    }
}

void fgbg(char* input) {
    pid_t pid;
    char cmd[strlen(input)+1];
    strcpy(cmd,input);

    pid=getnum(cmd);
    if (strstr(cmd, "fg") !=NULL) {
            foreground(pid);
     }
      else if(strstr(cmd, "bg") !=NULL){
            background(pid);
     } 
     
    
}



