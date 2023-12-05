/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
*/
#include "header.h"

void print_process_info(int pid) {
    char path[100];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening status file");
        return;
    }

    char line[256];
    char processState[10] = "";
    int processGroup = -1;
    char virtualMemory[20] = "";
    char executablePath[256] = "";
    while (fgets(line, sizeof(line), file)) {
        // printf("%s\n",line);
        if (strncmp(line, "State:", 6) == 0) {
            sscanf(line, "State:\t%s", processState);
        } else if (strncmp(line, "VmSize:", 7) == 0) {
            sscanf(line, "VmSize:\t%s", virtualMemory);
        } else if (strncmp(line, "Exe:", 4) == 0) {
            sscanf(line, "Exe:\t%s", executablePath);
        } else if (strncmp(line, "Pgrp:", 5) == 0) {
            sscanf(line, "Pgrp:\t%d", &processGroup);
        }
    }
    
    char path2[100];
    snprintf(path2, sizeof(path2), "/proc/%d/cwd", pid);

    char workingDirectory[256];
    ssize_t len = readlink(path2, executablePath, sizeof( executablePath) - 1);

    
    

    printf("Process ID: %d\n", pid);

    // Determine process status based on the state and background
    if (strcmp(processState, "R") == 0) {//Running
        printf("Process Status: R");
    } else if (strcmp(processState, "R+") == 0) {//Running (Foreground)
        printf("Process Status: R+");
    } else if (strcmp(processState, "S") == 0) {//Sleeping in an interruptible wait
        printf("Process Status: S");
    } else if (strcmp(processState, "S+") == 0) {//Sleeping in an interruptible wait (Foreground)
        printf("Process Status: S+");
    } else if (strcmp(processState, "Z") == 0) {//Zomnie
        printf("Process Status: Z"); 
    }

    printf("\nProcess Group: %d", processGroup);
    printf("\nVirtual Memory: %s", virtualMemory);
    printf("\nExecutable Path: %s\n", executablePath);

    fclose(file);
}

void execute_proclore(char *inp){//with proclore
	char comm[strlen(inp)+1];
	strcpy(comm,inp);
	
	char path[100];//processID
	
	size_t path_length = 0;
	
	char calculated_path[100]; // 
	int flag2=0;
	for (int i = 0; i <=strlen(comm); i++) {
	    if (flag2 == 1 ||  (comm[i]<='9' && comm[i]>='0') ) {
		flag2 = 1;
		calculated_path[path_length] = comm[i]; // Append to calculated_path
        	path_length++; 
		//strncat(calculated_path, &comm[i], 1); // Append to calculated_path
	    }
	}
	if (strlen(calculated_path) > 0 && calculated_path[strlen(calculated_path) - 1] == '\n')
	 {
	    calculated_path[strlen(calculated_path) - 1] = '\0';
	}
	
	strcpy(path, calculated_path);
	
	int processID=atoi(path); //paresed form proclore <processID>
	
	if(processID==0){    //no number id given
		processID=getpid();
	}
	else{
		//ok
	}
	
	print_process_info(processID);//prints for processID
	
	//printf("processID is %d\n",processID);
	
}


