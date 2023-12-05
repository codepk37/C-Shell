/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>  //for PATH_MAX 

//spec3 features

#define MAX_USERNAME_LEN 50
#define MAX_HOSTNAME_LEN 50
#define MAX_PATH_LEN PATH_MAX
#include "spec3.c"
*/
#include "header.h"

char old[MAX_PATH_LEN]="MAX_PATH_LEN";
char new[MAX_PATH_LEN]="MAX_PATH_LEN";

void updateold(char *curr){
	strcpy(old,new);
	strcpy(new,curr);
}

char *givold(){
	return old;
}

char* gethome(){  //getenv("HOME") replacement
	struct passwd *pw = getpwuid(getuid());
	char *homedir = pw->pw_dir;
	return homedir;
}




void print_prompt() {
    char username[50];
    char hostname[50];
    char cwd[MAX_PATH_LEN];

    // Get the username
    if (getlogin_r(username, sizeof(username)) != 0) {
        perror("getlogin_r");
        exit(EXIT_FAILURE);
    }

    // Get the hostname
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }

    // Get the current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    // Replace home directory path with '~'
    char *home = gethome();//getenv("HOME");
    //printf(" home :%s \n",home);
    if (home != NULL && strncmp(cwd, home, strlen(home)) == 0) {
        snprintf(cwd, sizeof(cwd), "~%s", cwd + strlen(home));
    }  //if removes /home/popos

    printf("<%s@%s:%s> ", username, hostname, cwd);
    //fflush(stdout);
    
    //strcpy(current,cwd);
    //change();
}



void extractchangedir(char input[100]){
	
	// Extract the directory path from the input
            char path[100];// = input + 0; // Skip "cd "
            strcpy(path,input);
             /*           
            if (strstr(input, "-") != NULL) { //remember 2 states
                path=givold();
                printf("path : %s\n",path);
                printf("activated\n");
                
            } 
            */
            
            
            
            //printf("size : %d\n",strlen(path));
            int len = strlen(path);
       	   
	    if (len > 0 && path[len - 1] == '\n') {
		path[len - 1] = '\0'; // Remove newline character
	    }
	   
	    
	    
	    char*home=gethome();
	    if(path[0]==' '){return;}
	    //printf("up :%s  :%s\n",gethome(),path);
	    
	    
	    if(strstr(path,"~/")!=NULL){ // ~/OSN  absolute path
            	char temp[100];
                snprintf(temp,sizeof(temp),"%s%s", home,path+1);// ~/OSN -> home/OSN
            	strcpy(path,temp);
            	
            	//printf("pa  :%s\n",path);
            	
            	//return;
           // 	
            }
            
	    
	    else if(path[0]=='\0' || path[0]=='~'){strcpy(path,gethome());} //cd , cd ~
            
            else if(strstr(path,"-")!=NULL){
            	 
            	
            	strcpy(path,givold());
            	//printf("Going to previous directory: %s\n", path);
            }
            
            
            // Change the working directory
            //printf("- %s",path);
            if (chdir(path) != 0  ) {
                perror("chdir ");
                
            }
            else{
            	//printf("%s\n",path);
            	if (getcwd(path, sizeof(path)) == NULL) {
			perror("updating cd - :");
			exit(EXIT_FAILURE);
	        }
	        printf("%s\n",path);
            	updateold(path);
            }
            
            //printf("[path : %s",path);
            /*
            const char *delimiters = " ";
	    char *tok;
	    char *saveptr = NULL;
	    tok = strtok_r(path, delimiters, &saveptr);
	    
	    while (tok != NULL) {
		printf("Directory argument: %s\n", tok);
		
		// Change the working directory
		if (chdir(tok) != 0) {
		    perror("chdir");
		}
		
		tok = strtok_r(NULL, delimiters, &saveptr);
	    }
	    */
}


