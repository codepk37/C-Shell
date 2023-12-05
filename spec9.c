

#include "header.h"

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h*/
//PASSED  :WORKING FOR ALL SYSTEM AND USER DEFINED  

/////////////////////////////


void solve(char *comm);

char* removespace(const char* input) {
    // Calculate the length of the input string
    size_t input_length = strlen(input);

    // Allocate memory for the output string (maximum length is the same as input)
    char* output = (char*)malloc(input_length + 1);  // +1 for the null terminator

    if (output == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    size_t j = 0;  // Index for the output string

    // Iterate through the input string and copy non-space/non-newline characters to the output
    for (size_t i = 0; i < input_length; i++) {
        if (input[i] != ' ' && input[i] != '\n') {
            output[j] = input[i];
            j++;
        }
    }

    // Null-terminate the output string
    output[j] = '\0';

    return output;
}


void print_back_terminal() { //STDOUT_FILENO -> stdout
    // Explicitly reopen standard output (stdout) to the terminal
    freopen("/dev/tty", "w", stdout);
    printf("Back to terminal\n");
}

void redirect_output_in_file(char output_file_name[250],int append_mode) {
    // Determine the file open mode based on the append_mode parameter
    int open_mode;
    if (append_mode) {
        open_mode = O_WRONLY | O_CREAT | O_APPEND; // Append mode
    } else {
        open_mode = O_WRONLY | O_CREAT | O_TRUNC;  // Overwrite mode
    }

    // Open the output file
    int output_fd = open(output_file_name, open_mode, 0644);
    
    
    if (output_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Redirect standard output (stdout) to the output file descriptor
    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    // Close the file descriptor for the output file (stdout is still redirected)
    close(output_fd);
}


///////////////////////


void io(char * command) {
    // Input string
    char input[strlen(command)+1];
    strcpy(input,command);
    //char input[] = " echo ppppssdneifdidw  >  pavan.txt  ";

    // Delimiter
    const char *delimiter = ">>";

    // Token variables
    char *token;
    char firstPart[250];
    char secondPart[250];
    char *saveptr;

    // Use strtok_r to find the first occurrence of the delimiter
    token = strtok_r(input, delimiter, &saveptr);

    // Check if the delimiter was found
    if (token != NULL) {
        // The first part is before the delimiter
        strcpy(firstPart ,token);
        
	char searchChar = '<', replaceChar = ' ';// Replace '<' with a space  -> directly send in execv()
   	 for (int i = 0; firstPart[i] != '\0'; i++) {if (firstPart[i] == searchChar) {firstPart[i] = replaceChar;}if (firstPart[i] == '\n'){firstPart[i]='\0';}}
        
        // Use strtok_r again to find the second part
        token = strtok_r(NULL, delimiter, &saveptr);
	
        if (token != NULL) {
            // The second part is after the delimiter
            strcpy(secondPart , removespace(token));//space and newline
            
            //append mode based on the delimiter
            int append_mode=0;
            if(strstr(command, ">>")){append_mode=1;}
            	    
	    
            // Print the two parts
            //printf("First Part:%s.", firstPart);
            //printf("Second Part:%s.", secondPart);  make split: remove spaces
            
            redirect_output_in_file(secondPart,append_mode);
            solve(firstPart);
            //system(firstPart);
            print_back_terminal();
            
            
            
        } else {
            //printf("Delimiter not found in the string.\n");
            //no need to redirect in file
            solve(firstPart);  //system(firstPart);
        }
    } else {
        //printf("Delimiter not found in the string.\n");
    }
    
    ////printf("normal stdout\n");

    return ;
}




/*
  DUP2 FOUNDATION
int main() {
    // Redirect input from a file (input.txt)
    
    //int input_fd = open("inpio.txt", O_RDONLY);
    //if (input_fd == -1) {
    //    perror("open");
    //    exit(EXIT_FAILURE);
    //}

    // Redirect output to a file (output.txt)
    int output_fd = open("outio.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Redirect standard input (stdin) to input_fd
    //if (dup2(input_fd, STDIN_FILENO) == -1) {
    //    perror("dup2");
    //    exit(EXIT_FAILURE);
    //}

    // Redirect standard output (stdout) to output_fd
    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    // Close the file descriptors that are no longer needed
    //close(input_fd);
    close(output_fd);

    // Now, any input read will come from input.txt, and output will go to output.txt
    printf("This is written to output.txt through redirection.\n");
    loop();  //in antotehr file
    printf(" hello written in printf Real ");
    fflush(stdout);
  
  
    // Explicitly reopen standard output (stdout) to the terminal
    freopen("/dev/tty", "w", stdout);
    printf("Hello written in printf Real\n");
    
    //char buffer[256];
    //scanf("%s", buffer); // Reads from input.txt   accpets till space or newline
    //printf("Read from input.txt: %s\n", buffer); 
    //scanf("%s", buffer); // Reads from input.txt
    //printf("Read from input.txt: %s\n", buffer);

    return 0;
}*/
