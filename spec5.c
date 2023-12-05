/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_HISTORY_SIZE 15  // Maximum number of recent commands to store
#define MAX_COMMAND_LENGTH 100
#define HISTORY_FILE "command_history.txt"

struct CommandHistory {
    char history[15][MAX_COMMAND_LENGTH];
    int size;
    int current;
};
*/
#include "header.h"

void initHistory(struct CommandHistory *history) {
    history->size = 0;
    history->current = -1;
    for (int i = 0; i < 15; i++) {
        history->history[i][0] = '\0';
    }
}

void tokenize_solve(char input[200]){
	
	const char *para = ";";
        char *tok;
        char *saveptr1 = NULL; // Save pointer for strtok_r
	tok = strtok_r(input, para, &saveptr1);

        while (tok != NULL) {
            
            if (strstr(tok, "&") != NULL) {
                char inp[strlen(tok) + 1];  //made new str = tok
                strcpy(inp, tok);    

                int atlast = 0;
                if (inp[strlen(inp) - 2] == '&') {
                    atlast = 1;
                }

                int totaland = givecount(inp, '&');

                const char *para_and = "&";  //parse on &
                char *new_tok;
                char *saveptr2 = NULL; // Save pointer for strtok_r
                new_tok = strtok_r(inp, para_and, &saveptr2);

                while (new_tok != NULL) {     
                    char st[strlen(new_tok) + 3];
                    strcpy(st, new_tok);
                    if (totaland > 0) {       //add & at end ,only if ori
                        totaland--;
                        strcat(st, "&");    //concatenate & at last
                    }
                    
                    //printf("new_tok with & %d :%s\n",strlen(st), st);
                    if(strlen(st)>1){
                    	
                    	//printf("main :%s\n",st);
                    	solve(st);
                    }
                    new_tok = strtok_r(NULL, para_and, &saveptr2);
                }

                tok = strtok_r(NULL, para, &saveptr1);
            } 
            else{
            	
                solve(tok);
                //printf("---solve comp\n");
                tok = strtok_r(NULL, para, &saveptr1);
            }
        }	


}

void addToHistory(struct CommandHistory *history, const char *command) {
    if (history->size > 0 && strcmp(history->history[history->size - 1], command) == 0) {
        return; // Don't store if it's the same as the last executed command
    }

    if (history->size == MAX_HISTORY_SIZE) {
        for (int i = 0; i < MAX_HISTORY_SIZE - 1; i++) {
            strcpy(history->history[i], history->history[i + 1]);
        }
        strcpy(history->history[MAX_HISTORY_SIZE - 1], command);
    } else {
        strcpy(history->history[history->size], command);
        history->size++;
    }
    history->current = history->size - 1;

    // Save history to file
    // FILE *historyFile = fopen(HISTORY_FILE, "w");
    // if (historyFile) {
    //     for (int i = 0; i < history->size; i++) {
    //         fprintf(historyFile, "%s\n", history->history[i]);
    //     }
    //     fclose(historyFile);
    // }
}




void loadHistoryFromFile(struct CommandHistory *history) {
    FILE *file = fopen("history.txt", "r");
    if (file == NULL) {
        return;
    }
    
    int i = 0;
    while (fgets(history->history[i], MAX_COMMAND_LENGTH, file) != NULL && i < 15) {
        // Remove newline character if present
        size_t length = strlen(history->history[i]);
        if (length > 0 && history->history[i][length - 1] == '\n') {
            history->history[i][length - 1] = '\0';
        }
        i++;
    }
    
    history->size = i;
    
    fclose(file);
}

void saveHistoryToFile(const struct CommandHistory *history) {
    FILE *file = fopen("history.txt", "w");
    if (file == NULL) {
        perror("Error opening history file");
        return;
    }
    
    for (int i = 0; i < history->size; i++) {
        fprintf(file, "%s\n", history->history[i]);
    }
    
    fclose(file);
}


//
void displayHistory(struct CommandHistory *history) {
    printf("Command History:\n");
    for (int i = history->size > 15 ? history->size - 15 : 0; i < history->size; i++) {
        printf("%d: %s\n", i + 1, history->history[i]);
    }
}
//
char * executeFromHistory(struct CommandHistory *history, int index) {  //
    if (index >= 1 && index <= history->size) {
        
        //printf("# output\n%s\n", history->history[history->size - index]);
        return history->history[history->size - index]; //returns string command
        //system(history->history[history->size - index]);
    } else {
        printf("Invalid index.\n");
    }
    return NULL;
}


int parseIndexFromCommand(const char *command) { //parse index from string
    int index;
    if (sscanf(command, "pastevents execute %d", &index) == 1) {
        return index;
    }
    return -1; // Return -1 for invalid format
}


char* execute_pastevents(char* inp,int in){  //main converted
	char command[strlen(inp)+1];
	strcpy(command,inp);
	
	char * ans=NULL;  //to return last executed** 
	
	struct CommandHistory history;
    	initHistory(&history);
    	loadHistoryFromFile(&history); // Load history from file

    //   struct termios oldTermios, newTermios;//no use here
    //   tcgetattr(STDIN_FILENO, &oldTermios); //putting the terminal into non-canonical mode and disabling character echoing. 
    //   newTermios = oldTermios;
    //   newTermios.c_lflag &= ~(ICANON | ECHO);
    //   tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);

      //printf("Enter a command: ");
      //fflush(stdout);
      //we have command now
      if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
      }
      
      // Handle the command and add to history
        if (strstr(command, "pastevents purge") !=NULL && in==1) {
            // Clear history without adding the command to history
            initHistory(&history);
            remove("history.txt"); // Remove the history file
            printf("History cleared.\n");
            
        }
        else if (strstr(command, "pastevents execute") !=NULL && in==1) {
            // Extract index and execute the corresponding command
            int index=parseIndexFromCommand(command);
                if (index != -1) {
                    ans=executeFromHistory(&history, index);
                    if(ans!=NULL){ //took tokenizing from main
                    	tokenize_solve(ans);
                    }
                } else {
                    printf("Invalid command format.\n");
                }
        }  
        
        else if (strstr(command, "pastevents") !=NULL && in==1) {
            // Show history
            if (history.size > 0) {
                displayHistory(&history);
            } else {
                printf("No history available.\n");
            }
        } 
        
        else if (strstr(command, "pastevents") == NULL && in==20) {
            addToHistory(&history, command);
           //printf("added to history\n", command); ***
        }
        
        //e
        //printf("Enter a command: ");
        //fflush(stdout);
        if(in==20){
        saveHistoryToFile(&history);
        }
      //free(command); // Free the dynamically allocated memory
      
      //tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
      
      return ans;
      //return string line
      
}

