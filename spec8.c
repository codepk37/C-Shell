//    home should start with :  /home/popos/OSN  i.e. atart with slash '/'
/*#define MAX_TOKENS 10 // Maximum number of tokens (adjust as needed)
#define MAX_TOKEN_LENGTH 50 // Maximum length of each token (adjust as needed)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH_LENGTH 1024
#define MAX_RESULT_LENGTH 100
*/
#include "header.h"

int use_e_flag = 0; // Initialize the flag
#define MAX_BUFFER_SIZE 1024 // Or whatever size you need

void seek_directory(const char *target, const char *path, int is_dir, int is_file, int is_exact_match) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    
    if (!dir) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    
    int found_count = 0;
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        struct stat statbuf;
        char entry_path[MAX_PATH_LENGTH];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", path, entry->d_name);
        
        if (stat(entry_path, &statbuf) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }
        
        if (S_ISDIR(statbuf.st_mode)) {
            if (is_dir && (is_exact_match ? (strcmp(target, entry->d_name) == 0) : strstr(entry->d_name, target) != NULL)) {
                printf("\033[34m%s/%s\033[0m\n", path, entry->d_name); // Print in blue
                found_count++;
            }
            
            if (!is_file) {
                seek_directory(target, entry_path, is_dir, is_file, is_exact_match);
            }
        } else if (S_ISREG(statbuf.st_mode)) {
            if (is_file && (is_exact_match ? (strcmp(target, entry->d_name) == 0) : strstr(entry->d_name, target) != NULL)) {
                printf("\033[32m%s/%s\033[0m\n", path, entry->d_name); // Print in green
                found_count++;
            }
        }
    }
    
    closedir(dir);
    
    if (found_count == 0) {
        //printf("No match found!\n");
    }
}

void execute_seek(char * comm){
	char input[200];
	strcpy(input,comm);
	input[strcspn(input, "\n")] = '\0';
    char *tokens[MAX_TOKENS];
    
    // Use strtok to split the input string into tokens
    int token_count = 0;
    char *token = strtok(input, " ");
    
    while (token != NULL && token_count < MAX_TOKENS) {
        tokens[token_count] = strdup(token); // Copy the token into the array
        token_count++;
        token = strtok(NULL, " ");
    }
    
    // Process the tokens (similar to using argv)
    //if (token_count < 3) {
    //  fprintf(stderr, "Usage: %s <flags> <search> <target_directory>\n", tokens[0]);
    //    exit(EXIT_FAILURE);
    //}
    
    
    int is_dir = 1, is_file = 1, is_exact_match = 0;

    for (int i = 1; i < token_count - 2; i++) {
        if (strcmp(tokens[i], "-d") == 0) {
            is_file = 0;
        } else if (strcmp(tokens[i], "-f") == 0) {
            is_dir = 0;
        } else if (strcmp(tokens[i], "-e") == 0) {
            is_exact_match = 1;
        } else {
            fprintf(stderr, "Invalid flags!\n");
            exit(EXIT_FAILURE);
        }
    }

    char *search = tokens[token_count - 2];
    char *target_directory = tokens[token_count - 1];
    printf(" %s  %s  \n",search,target_directory);
    // Free allocated memory for strdup'd tokens
    for (int i = 0; i < token_count; i++) {
        //free(tokens[i]);
    }
      ///paring done from string		

   

    char resolved_target_directory[MAX_PATH_LENGTH];
    realpath(target_directory, resolved_target_directory);

    seek_directory(search, resolved_target_directory, is_dir, is_file, is_exact_match);

    return ;
}

