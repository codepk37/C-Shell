
//process in bg -> fg ,ctrl+Z works
//sleep 5 ,ctrl+Z stays in prompt

#include"header.h"
//finds cd  ,no need cd to be at start index[0]
//here  parsing parts ,sending remaing part left to function (e.g . after cd ) 
//strcmp(tok,cd) ->0 if both string are same

//strcpy(array,st pointer);  //strcpy(input,"ls");

char* execute_pastevents(char* inp,int in);
// Global variable to store the PID of the foreground process
pid_t foregroundProces = -1;

void handle_sigint(int signum) { // handle the SIGINT signal (Ctrl + C)
    if (foregroundProces != -1) {
        // Send SIGINT to the foreground process
        printf("sigint called\n");
        kill(foregroundProces, SIGINT); //kills only foreground no exit
    }
}
//pid_t foregroundProcess = -1;
void sigtstpHandler(int signum) {  //ctrl+Z
    if (foregroundProces != -1) {
        // Send SIGTSTP to the foreground process
        printf("sigtstp called\n");
        tcsetpgrp(STDIN_FILENO, getpgrp());// ensure that the process calling the handler becomes the foreground process group leader
        kill(foregroundProces, SIGTSTP);
	printf("[%d] Stopped\t\t(background)\n", foregroundProces);
	

    }
}
void handle_ctrld() {
		//KILL WITH sigterm	
    printf("Logging out...\n"); 	
    kill(0, SIGTERM);// 0 means the signal is sent to all processes
    //even shell sigint =sigterm
       
    exit(0); // Terminate your shell
}


int main() {
    signal(SIGINT, handle_sigint); //calls handle_sigint   c
    signal(SIGTSTP, sigtstpHandler);//calls sigtstpHandler Z
    //signal(EOF, handle_ctrld); // Handle Ctrl+D
    
   
    int stop = 1;
    while (stop) {
        print_prompt();

        char *input = NULL;
        size_t n = 50;
        //instead of fgets(fixed memory) ,use getline
        ssize_t read_bytes =getline(&input, &n, stdin);//reallocates if more memory required
        
        if (read_bytes == -1) {  //ctrl +d reads eof ,therefore no input
            // Ctrl+D (EOF) was detected
            handle_ctrld();
            
        }
        
        
        ////////////////pastevents
        //if (strstr(input, "pastevents") != NULL)  //input has pastevents
        
        execute_pastevents(input,20); //just save in pastevents          
        
        //continue;
        /*****
      	 //  works even for ;   ; ,just error with sleep 5 & ,so parse on basis of  ;  ;  then work individually taking care of  '&'  if occurs
      	 
      	char input[MAX_INPUT_LENGTH];
        strcpy(input,"  ls -l;sleep 5  ;    echo euwdef hi;echo 32141;cd Copies;echo hi");
        system(input);
        */

        const char *para = ";";
        char *tok;
        char *saveptr1 = NULL; // Save pointer for strtok_r

        tok = strtok_r(input, para, &saveptr1);

        while (tok != NULL) {
            if (strstr(tok, "exit") != NULL) {
                printf("seeusoon:)\n");
                stop = 0;
                break;
            } 
            else if (strstr(tok, "&") != NULL) {
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
            	//printf("not &\n");
                //cd printf("outer with ; %s\n", tok);
                //printf("main :%s\n",tok);
                solve(tok);
                //printf("---solve comp\n");
                tok = strtok_r(NULL, para, &saveptr1);
            }
        }
    }

	/*MULTITHREADING  for sleep bg	
	pthread_cancel(bg_thread);
    pthread_join(bg_thread, NULL);
	*/

    return 0;
}

/****
	const char *para=" ;";//parameter parsing
	char * tok;
	char* cd="cd";
	tok=strtok(input,para);	
	//see strtok.c 
        if (strcmp(tok, cd) == 0) {//yes first part is cd
        	tok=strtok(0,para);//next part 
        	//if starts with cd ___   
                extractchangedir(tok);//sending next part
            
        }
        */
//changes are on way 
//changes are on way 
//changes are on way 
//changes are on way 
//changes are on way 
//changes are on way 
//changes are on way 

//changes are on way 
//changes are on way 
//changes are on way 
//changes are on way 

//changes are on way 
//changes are on way 


//changes are on way 
//changes are on way 
//changes are on way 

//changes are on way 
//changes are on way 
//changes are on way 
