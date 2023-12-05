
#include "header.h"

/*
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>*/

void execute_ping(char * command) {
    char input[strlen(command)+1];
    strcpy(input,command);


    char* pid_str;
    char* signal_str;
     
    strtok(input, " ");  //ping 
    
    pid_str = strtok(NULL, " "); 
    signal_str = strtok(NULL, " "); //string

    if (pid_str == NULL || signal_str == NULL) {
        printf("Invalid input format. Please provide PID and signal number.\n");
        return ;
    }
    //printf("pid %s , signal %s\n",pid_str,signal_str);

    pid_t pid;
    int signal_number;

    // Parse the PID and signal number to int
    if (sscanf(pid_str, "%d", &pid) != 1 || sscanf(signal_str, "%d", &signal_number) !=1){
        printf("Invalid PID or signal number.\n");
        return ;
    }
//errno is a global variable,set by system calls and library functions when an error occurs.
    // Check if the process with the given PID exists
    if (kill(pid, 0) == -1) { 
        if (errno == ESRCH) {// means "No such process."
            printf("No such process found\n");
        } else {
            perror("kill");//some other error
        }
        return ;
    }

    // Calculate the actual signal number based on modulo 32
    int actual_signal_number = signal_number % 32;

    // Send the signal to the process  ALL THINGS GO HERE *****
    if (kill(pid, actual_signal_number) == -1) {
        perror("kill");
        return ;
    }

    printf("Sent signal %d to process with pid %d\n", actual_signal_number, pid);

    return ;
}

