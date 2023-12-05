
#include "header.h"
//DONE SPEC12

/*
#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>*/

// Define a structure to hold process information
/*
struct ProcessInfo {
    int pid;
    char state;
    char cmd[256];
};
*/

// Custom comparison function for qsort to sort by command name
int compareByCmdName(const void *a, const void *b) {  //for sorting
    return strcmp(((struct ProcessInfo *)a)->cmd, ((struct ProcessInfo *)b)->cmd);
}

void activities() {
    DIR *dir;
    struct dirent *ent;
    int fd_self, fd;
    char *tty;
    char cmd[256], tty_self[256], path[256], stat_path[256];
    FILE *file;

    struct ProcessInfo processInfos[256]; // Assuming a maximum of 256 processes
    int numProcesses = 0;

    dir = opendir("/proc");  ///proc directory to access information about running processes
    fd_self = open("/proc/self/fd/0", O_RDONLY);
    sprintf(tty_self, "%s", ttyname(fd_self));// terminal device of the current process

    while ((ent = readdir(dir)) != NULL) {//iterate through entries in the /proc directory
	 if (isdigit(ent->d_name[0])) {
		strcpy(path, "/proc/");
		strcat(path, ent->d_name); //
		strcat(path, "/fd/0");
		fd = open(path, O_RDONLY);
		tty = ttyname(fd);

		if (tty && strcmp(tty, tty_self) == 0) { // checks if it matches the terminal device of the current process.
		    strcpy(stat_path, "/proc/");
		    strcat(stat_path, ent->d_name);//process ID (PID) in string form
		    strcat(stat_path, "/stat");
		    file = fopen(stat_path, "r");//proc/[pid]/stat
		    int pid;
		    char state;
		    fscanf(file, "%d %s %c", &pid, cmd, &state);

		    // Store process information in the array
		    processInfos[numProcesses].pid = pid;
		    processInfos[numProcesses].state = state;
		    strcpy(processInfos[numProcesses].cmd, cmd);
		    numProcesses++;

		    fclose(file); //file descriptors are closed.
		 }

		close(fd);// descriptors are closed.
	   }
    }


    closedir(dir); //directory are closed.
    close(fd_self);

    // qSort the processInfos array lexicographically by command name
    qsort(processInfos, numProcesses, sizeof(struct ProcessInfo), compareByCmdName);

    // Print the sorted list
    printf("PID\tSTATE\tCMD\n");
    for (int i = 0; i < numProcesses; i++) {
    	const char *state_str ;
    	if(processInfos[i].state=='R'){state_str="Running";}
    	else if(processInfos[i].state=='T'){state_str="Stopped";}
    	if(processInfos[i].state=='S'){state_str="Running";} //Sleeping
    	
        //printf("%d:\t%s\t-%s\n", processInfos[i].pid,  processInfos[i].cmd,state_str );
        printf("%d:\t%s\t-%s\n", processInfos[i].pid,  processInfos[i].cmd, state_str );
    }

    return ;
}



/*
struct ProcessInfo {
    int pid;
    char state;
    char cmd[256];
};

// Custom comparison function for qsort to sort by command name
int compareByCmdName(const void *a, const void *b) {
    return strcmp(((struct ProcessInfo *)a)->cmd, ((struct ProcessInfo *)b)->cmd);
}

void activites() {
    DIR *dir;
    struct dirent *ent;
    int fd_self, fd;
    char *tty;
    char cmd[256], tty_self[256], path[256], stat_path[256];
    FILE *file;

    struct ProcessInfo processInfos[256]; // Assuming a maximum of 256 processes
    int numProcesses = 0;

    dir = opendir("/proc");
    fd_self = open("/proc/self/fd/0", O_RDONLY);
    sprintf(tty_self, "%s", ttyname(fd_self));

    while ((ent = readdir(dir)) != NULL) {
        if (isdigit(ent->d_name[0])) {
            sprintf(path, "/proc/%s/fd/0", ent->d_name);
            fd = open(path, O_RDONLY);
            tty = ttyname(fd);

            if (tty && strcmp(tty, tty_self) == 0) {
                sprintf(stat_path, "/proc/%s/stat", ent->d_name);
                file = fopen(stat_path, "r");
                int pid;
                char state;
                fscanf(file, "%d %s %c", &pid, cmd, &state);

                // Store process information in the array
                processInfos[numProcesses].pid = pid;
                processInfos[numProcesses].state = state;
                strcpy(processInfos[numProcesses].cmd, cmd);
                numProcesses++;

                fclose(file);
            }

            close(fd);
        }
    }

    closedir(dir);
    close(fd_self);

    // Sort the processInfos array lexicographically by command name
    qsort(processInfos, numProcesses, sizeof(struct ProcessInfo), compareByCmdName);

    // Print the sorted list
    printf("PID\tSTATE\tCMD\n");
    for (int i = 0; i < numProcesses; i++) {
    	const char *state_str = ( processInfos[i].state == 'R') ? "Running" : "Stopped";
        printf("%d:\t%s\t-%s\n", processInfos[i].pid,  processInfos[i].cmd,state_str );
    }

    return ;
}
*/






/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


char* shell_name=NULL;
// Function to find the shell name
char* findShellName() {

    //char* shell_name = NULL;
    // Get the current process ID
    pid_t my_pid = getpid();

    // Execute the 'ps' command and capture its output
    FILE* ps_output = popen("ps -p $PPID -o comm=", "r");
    if (ps_output != NULL) {
        char buffer[256];
        if (fgets(buffer, sizeof(buffer), ps_output) != NULL) {
            // Remove trailing newline character
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }
            shell_name = strdup(buffer); // Duplicate the string
        }
        pclose(ps_output);
    }

    //return shell_name;
}

////


void func() {
    pid_t my_pid = getpid();
    pid_t parent_pid = getppid();
    pid_t group_pid = getpgrp();
    pid_t session_pid = getsid(0);  // 0 means the current process

    printf("Process ID: %d\n", my_pid);
    printf("Parent Process ID: %d\n", parent_pid);
    printf("Process Group ID: %d\n", group_pid);
    printf("Session ID: %d\n", session_pid);

    // Get the directory path for the /proc directory
    char proc_dir[256];
    snprintf(proc_dir, sizeof(proc_dir), "/proc/%d/exe", my_pid);

    // Execute the 'ps' command and capture its output
    printf("List of process names spawned by your shell (sorted lexicographically):\n");
    FILE *ps_output = popen("ps -eo comm", "r");
    if (ps_output == NULL) {
        perror("popen");
        return ;
    }

    // Skip the header line
    char buffer[256];
    fgets(buffer, sizeof(buffer), ps_output);

    // Create an array to store the process names
    char process_names[1024][256];
    int num_processes = 0;

    // Read and store the process names
    while (fgets(buffer, sizeof(buffer), ps_output) != NULL) {
        char process_name[256];
        sscanf(buffer, "%s", process_name);

        // Check if the process name starts with the shell's name
        if (strstr(process_name, shell_name) != NULL) {
            strcpy(process_names[num_processes], process_name);
            num_processes++;
        }
    }

    // Close the 'ps' command output
    pclose(ps_output);

    // Sort and print the process names
    for (int i = 0; i < num_processes; i++) {
        for (int j = i + 1; j < num_processes; j++) {
            if (strcmp(process_names[i], process_names[j]) > 0) {
                char temp[256];
                strcpy(temp, process_names[i]);
                strcpy(process_names[i], process_names[j]);
                strcpy(process_names[j], temp);
            }
        }
    }

    for (int i = 0; i < num_processes; i++) {
        printf("%s\n", process_names[i]);
    }

    return ;
}


////

void activites(){  //int main() 
    findShellName();

    if (shell_name != NULL) {
        printf("Shell Name: %s\n", shell_name);

        // Free allocated memory
        free(shell_name);
    } else {
        printf("Failed to determine shell name.\n");
    }
    func();
}
*/
