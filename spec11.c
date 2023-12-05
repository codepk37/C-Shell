
#include "header.h"
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>*/


//UNDERSTAND IT ,till concepts

void solve(char * comm);

int ispipeincorrect(char *st){
	int flag=1;
	for(int i=0;i<strlen(st);i++){
		if(st[i]=='|' && flag==1){
		    return 1;
		}
		else if(st[i]=='|'){
		    flag=1;
		}
		else if(st[i]!=' '){
		    flag=0; //alphabet or number 
		}
	}
	if(flag==1){return 1;}
	return 0;
}

void pipe_io(char* command){
    
    char input[strlen(command)+1];
    strcpy(input,command);
    // Remove trailing newline character
    input[strcspn(input, "\n")] = '\0';  //strcspn(str,subst) ,index of 1st seen in str 
    
    if(ispipeincorrect(input)){
    	printf("Invalid use of pipe\n"); //ERROR //perror
    	return ;
    }
    
    char *commands[10];
    int num_commands = 0;

    // Tokenize the input based on pipes
    char *token = strtok(input, "|");
    while (token != NULL) {
        commands[num_commands] = token;
        num_commands++;
        token = strtok(NULL, "|");
    }

    if (num_commands < 2) {
        fprintf(stderr, "Invalid use of pipe\n");
        exit(EXIT_FAILURE);
    }

    int pipes[num_commands - 1][2];  // Create pipes,n-1 pipe

    for (int i = 0; i < num_commands - 1; i++) {//n-1 pipe
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_commands; i++) {  // n command fork
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            if (i > 0) {
                // Redirect stdin to the read end of the previous pipe
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][0]);  // Close read end of the previous pipe
            }

            if (i < num_commands - 1) {    //till= last pipe
                // Redirect stdout to the write end of the current pipe
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][1]);  // Close write end of the current pipe
            }

            // Close all other pipe ends
            for (int j = 0; j < num_commands - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // Execute the command using /bin/sh
            //execl("/bin/sh", "sh", "-c", commands[i], NULL);
            solve(commands[i]);
	    //perror("solve");
            // If execl fails, print an error message
            //perror("execl");
            exit(EXIT_FAILURE);
        }
    }

    // Close all pipe ends in the parent process
    for (int i = 0; i < num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Wait for all child processes to finish
    for (int i = 0; i < num_commands; i++) {
        wait(NULL);
    }

    return ;
}
