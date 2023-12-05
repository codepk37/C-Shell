/*
// Structure to hold information about background processes
typedef struct {
    pid_t pid;
    char command[MAX_INPUT_LENGTH];
} BackgroundProcess;
*/

#include "header.h"
extern pid_t foregroundProces;
// Structure to hold information about background processes


BackgroundProcess background_processes[10]; // Assuming a maximum of 10 background processes
int wer=0;
int num_background_processes = 0;

void run_command(char *args[], int is_background) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {  //it replaces the current process with the new program,
            perror("execvp");
            exit(EXIT_FAILURE);
            // here only replaces the code in the child process.
            // its the child doing execvp not parent, so parent control flow still be in parent function

        }
    } else if (pid > 0) {
        // Parent process
        if (!is_background) {
            int status;
            foregroundProces=pid;
            waitpid(pid, &status, WUNTRACED); //TO HANDLE CTRL+Z    //WUNTRACED tells waitpid to return if a child has stopped (e.g., due to a SIGSTOP signal) in addition to returning if a child has terminated.
            foregroundProces=-1;
           
            // Print elapsed time for foreground process
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                 freopen("/dev/tty", "w", stdout); //io()
                // 1)it means the child process didn't terminate due to a signal or error
                // 2)indicating a successful exit. exitstatus==0
                printf("Foreground process (%s) took more than 2 seconds to run.\n", args[0]);
            }
        } else {
            // Save background process information
            background_processes[num_background_processes].pid = pid;
            strcpy(background_processes[num_background_processes].command, args[0]);
            num_background_processes++;
            printf("[%d] %d\n",1+(wer++)%10, pid);
        }
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void check_background_processes() {
    int i;
    for (i = 0; i < num_background_processes; i++) {
        int status;
        pid_t pid = waitpid(background_processes[i].pid, &status, WNOHANG);//WNOHANG option is used to check the status of a child process without blocking the parent process. 
        
        // returns 0:       child process is still running 
        // returns the PID: child process has terminated 
        
        if (pid > 0) {
            printf("(%s) with pid %d ", background_processes[i].command, pid);
            if (WIFEXITED(status)) {
                printf("exited normally \n");
            } else if (WIFSIGNALED(status)) {  //evaluates to true if the child process terminated due to a signal, such as SIGTERM or SIGSEGV
                printf("exited abnormally \n");
            } else {
                printf("exited.\n");
            }
            // Remove process from the list
            num_background_processes--;
            if (i < num_background_processes) {
                background_processes[i] = background_processes[num_background_processes];
            }
        }
    }
}


void command_execute(char *comm){ //with &
	char input[MAX_INPUT_LENGTH];
	strcpy(input,comm);
    
    // printf("comm %s\n",input); it even considers only 'enter' as command ,
    //so after 'enter' or any command, it checks completed bg process, in check_background_processes(); 
	
    // Remove newline character
        input[strcspn(input, "\n")] = '\0';	
        
        int is_background = 0;
        if (input[strlen(input) - 1] == '&') {
            is_background = 1;
            input[strlen(input) - 1] = '\0'; // Remove '&' from the input
        }
        
        char *args[MAX_INPUT_LENGTH];
        int arg_count = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; //

        // Run the command
        run_command(args, is_background);
        
        // Check and display ended background processes
        check_background_processes(); //whenever a process is executed ,fg or bg
                                     //parent control go checks by this func
    
    return ;

}



//child is going to exwcu&te
//if bg==1 ,parent waits for it(child to complete)
//if bg==0 , bhad me ja child
/*
void command_execute(char *comm, int bg) {
	
	static int t=0;
	t=(t+1)%10; //   1 ->10 -> 1  job no.
	
	int c=t;   //avoid backtracing at exiting multiple
	//printf("command :%s ,bg: %d",comm,bg);
    int pid =1;// fork();

    if (pid == 0) {
        // Child process
        int s=system(comm);      
        
        /*pid_t w_pid=0;
	do{
		w_pid=waitpid(pid,NULL,WNOHANG);
		sleep(1);
	}while(w_pid==0);	
	printf("child exited %s %d\n",comm,pid);
	//* /        
	//printf("in child\n");
        if (strstr(comm, "sleep") != NULL && bg==1) {
		        char inp[strlen(comm) + 1];  //made new str = tok
		        strcpy(inp, comm);    
		        
		        const char *para = " ";
			char *tok;
			char *saveptr1 = NULL; // Save pointer for strtok_r
			tok = strtok_r(inp, para, &saveptr1); //is sleep
			tok = strtok_r(NULL, para, &saveptr1); //is time
			
			//printf("time tok %d",atoi(tok));
			printf("sleep with pid %d exited normally # after %d seconds\n",getpid(),atoi(tok));
			return;			
		}
       }
       else if (pid > 0) {
        // Parent process
           if (!bg){
		    waitpid(pid, NULL, 0); //fg 
		    printf("fg\n");
           	   return;
           }
            else{
           	 printf("[%d] %d\n", c, pid);  // Print parent and child process IDs //not t as it is static
           	 return ;
           }
       }
      else{
       		 perror("fork");  // Print an error message if fork fails
       		 return;
       }
    
    //cursor comes for bg
      
	 return;     
}
*/



/*MULTITHREADING   -----for sleep 5& 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define MAX_INPUT_LENGTH 1024

pid_t bg_pid = -1; // Store the PID of the background process
pthread_mutex_t bg_mutex = PTHREAD_MUTEX_INITIALIZER;

void *background_checker(void *arg) {
    while (1) {
        pthread_mutex_lock(&bg_mutex);
        if (bg_pid != -1) {
            pid_t result = waitpid(bg_pid, NULL, WNOHANG);
            if (result != 0 && result != -1) {
                printf("Background process [%d] completed\n", result);
                bg_pid = -1; // Reset the stored PID
            }
        }
        pthread_mutex_unlock(&bg_mutex);
        sleep(1); // Adjust the interval as needed
    }
    return NULL;
}

void command_execute(char *comm, int bg) {
    pthread_mutex_lock(&bg_mutex);
    if (bg_pid != -1) {
        pid_t result = waitpid(bg_pid, NULL, WNOHANG);
        if (result != 0 && result != -1) {
            printf("Background process [%d] completed\n", result);
            bg_pid = -1; // Reset the stored PID
        }
    }
    pthread_mutex_unlock(&bg_mutex);

    pid_t pid = fork();

    if (pid == 0) {
        int s = system(comm);
        printf("Command completed: %s\n", comm);
        exit(s);
    } else if (pid > 0) {
        if (!bg) {
            waitpid(pid, NULL, 0);
        } else {
            printf("Background process started: %s [%d]\n", comm, pid);
            bg_pid = pid;
        }
    } else {
        perror("fork");
    }
}
*/

