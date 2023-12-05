#ifndef __SPEC2_H
#define __SPEC2_H

void run_command(char *args[], int is_background) ;
typedef struct {
    pid_t pid;
    char command[MAX_INPUT_LENGTH];
} BackgroundProcess;
void check_background_processes();
void command_execute(char *comm);

#endif
