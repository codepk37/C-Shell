/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10


int main2() {
    char input[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    int background = 0;

    while (1) {
        printf("Enter a command: ");
        fflush(stdout);

        // Read user input
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0'; // Remove newline

        if (strcmp(input, "exit") == 0) {
            break; // Exit the shell
        }

        // Tokenize the input into arguments
        char *token = strtok(input, " ");
        int argIndex = 0;
        while (token != NULL && argIndex < MAX_ARGS - 1) {
            args[argIndex] = token;
            token = strtok(NULL, " ");
            argIndex++;
        }
        args[argIndex] = NULL; // Null-terminate the arguments array

        // Check if the command should be run in the background
        if (argIndex > 0 && strcmp(args[argIndex - 1], "&") == 0) {
            background = 1;
            args[argIndex - 1] = NULL; // Remove the "&"
        } else {
            background = 0;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            
            // Execute the command
            execvp(args[0], args);
            
            // If execvp returns, there was an error
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            
            // If not in the background, wait for the child process to complete
            if (!background) {
                int status;
                waitpid(pid, &status, 0);
            }
        }
    }

    return 0;
}
*/
