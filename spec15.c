
#include "header.h"

/*
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <time.h>*/

int isNumber(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}
int getOwnPID() {  //pid of latest process
    // Open the special file /proc/self/stat to read process information.
     DIR *procDir;
    struct dirent *entry;
    int maxPID = -1;

    procDir = opendir("/proc");
    if (procDir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(procDir))) {
        if (isNumber(entry->d_name)) { //d_name= pid in string
            int pid = atoi(entry->d_name);
            if (pid > maxPID) {
                maxPID = pid;
            }
        }
    }//keeps track of the maximum PID found. The maximum PID represents the most recently created process on the system.

    closedir(procDir);

    if (maxPID != -1) {
        //printf("Most recently created process ID: %d\n", maxPID);
        //prints in return
        return maxPID;
    } else {
        printf("No processes found.\n");
        return -1;
    }

}
////////////////////  ??? dont know why would pid change at runtime
//////



/*         this was incorrect , first field issnt necessary latest process ,find the max pid possible
int getOwnPID() {  //pid of latest process
    // Open the special file /proc/self/stat to read process information.
    FILE* statFile = fopen("/proc/self/stat", "r");
    if (!statFile) {
        perror("Failed to open /proc/self/stat");
        return -1;
    }

    // Read the first field (process ID) from the file.
    int pid;
    if (fscanf(statFile, "%d", &pid) != 1) {
        perror("Failed to read process ID from /proc/self/stat");
        fclose(statFile);
        return -1;
    }

    fclose(statFile);
    return pid;
}
*/

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}// input is made available to the program character by character as soon as it's entered by the user, without waiting for Enter to be pressed.


int getnum(char*p);//repeated in spec14   ->parses numb from string
    

int neonate(char * command) {
    
    char input[strlen(command)+1];
    strcpy(input,command);
    
    int num=getnum(input);

    int time_arg = num;  //atoi(argv[2]);
    if (time_arg <= 0) {
        fprintf(stderr, "Invalid time_arg\n");
        return 1;
    }

    char c;
    
    int pid = getOwnPID();//not a system command ->so used proc/

    enableRawMode(); //not to display any char typed by keyboard
    

    while (1) {
    	struct timeval tv;
        tv.tv_sec = time_arg;//num sec
        tv.tv_usec = 0; //0 usec
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        int retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
        
        //even if no input ,still prints i.e. dosent stays in 'read()' imp

        if (retval == -1) {//retval =-1, error
            die("select");
        } else if (retval) {//+ve checks whether there is input available 
            if (read(STDIN_FILENO, &c, 1) == 1) {//
                if (c == 'x') {
                    break;
                }
            }
        } else {//0 timeout specified by tv has elapsed without any input
            pid= getOwnPID();
            printf("%d\n", pid);
            fflush(stdout);
        }
    }

    disableRawMode();//or Cooked mode :the entire line is sent to the program for processing after 'Enter'
    return 0;
}




