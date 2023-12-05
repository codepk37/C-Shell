#include "header.h"

/*#include<stdio.h>
#include "spec1.c"
#include "spec2.c"
#include "spec9.c"
#include "spec4.c"
#include "spec7.c"
#include "spec8.c"
#include  "spec11.c"
#include "spec12activities.c"
#include "spec13.c"
#include "spec14.c"
#include "spec15.c" 
#include"spec16.c"*/

void delay(){
	for(int i=0;i<10000;i++);
}
int givecount(char *st,char ch){
   int tot=0;
    for(int i=0;i<=strlen(st)-1;i++){
	    if(st[i]==ch){tot++;}
	    //printf(" %c",st[i]);
     }     
   //printf(" total & are :%d\n",tot);
   return tot;
    
}


void solve(char *command){
	
	//printf("time should 1 solve\n");
	char input[strlen(command)+1];
	strcpy(input,command);
	
	char orig[strlen(command)+1];
	strcpy(orig,command);
	
	//printf("orig %s",orig);
	
	//input contains single command ,as seperated by ; earlier
	
	//1
	const char *para=" ";//parameter parsing ' cd Copies ',para=" "
	char *tok;
	char* cd="warp";  //just change to warp
	char *saveptr3 = NULL; 
	tok = strtok_r(input, para,&saveptr3);
	
	//see strtok.c 
	if((strstr(orig,"<")!=NULL || strstr(orig,">")!=NULL ||strstr(orig,">>")!=NULL) &&  strstr(orig,"|")==NULL ){  //not for piping
        	//printf("comeleted io in solver\n");
        	io(orig);
            	return;
        	//function again calls  part 1 in solve() , >,>> ,part 2 inn taht file        	
        }
        else if(strstr(orig,"|")!=NULL){
        	//printf("in pipe solver\n");
        	pipe_io(orig);
        	return;
        }
        else if (strcmp(tok, cd) == 0) {//after cd
        	tok = strtok_r(NULL, para,&saveptr3);  //skipped cd
        	
        	//tok=strtok(0,para);
        	
        	while(tok!=NULL ){
        	        //printf("time should 1 solver:%s\n",tok);
			extractchangedir(tok);
			tok = strtok_r(NULL, para,&saveptr3); //next part 
		}      	
        	//tok = strtok(NULL, para); //next part 
		//extractchangedir(tok);       	
        	//if starts with cd ___   
                
                return;   
        }////// use tok only strstr(strstr,"cd")     
      
               
        //  peek -  ls  command specification 4
        else if(strstr(tok,"peek")!=NULL){
        	execute_ls(orig); //send full command to func
        	return;
        }
        
        //  pastevents  command specification 5
        //directly in main
        
        
        /// proclore 
        else if(strstr(tok,"proclore")!=NULL){
        	execute_proclore(orig);
        	return;
        	
        }
        
        ////seek
        else if(strstr(tok,"seek")!=NULL){
        	execute_seek(orig);
        	return;
        	
        }
        
        
        else if(strstr(tok,"activities")!=NULL){
        	activities();
        	return; //some warnings
        	
        }
        else if (strstr(input, "ping") != NULL) {
        	execute_ping(orig);
        	return;
    	}
    	else if (strstr(input, "fg") != NULL  ||strstr(input, "bg") != NULL){
    		fgbg(orig);
    		return;
    	}
    	else if(strstr(tok,"iMan")!=NULL){
        	iMan_comm(orig);
        	return; //some warnings
        	
        }
        else if(strstr(tok,"neonate")!=NULL){
        	neonate(orig);
        	return; //some warnings
        	
        }
        
	else if(strstr(orig,"pastevent")!=NULL){
			execute_pastevents(orig,1);
			return; //some warnings
			
	}
        
        
        
        
        //2echo 
        //orig is original command ,as input-> next word
        //int bg=0;  //default fg foreground
        //int len=strlen(orig);
        
        //if(orig[len-1]=='&'){// 
        //	bg=1; //in bg
        //	orig[len-1]='\0';//system() dosent recognize '&' so handle explicitly       
        //}
        //*********all system commands supporting & bg should come down *******//
        
        
        
        
        //printf("solver :%d %s\n",bg,orig);
        
        //printf("aboev comm %s\n",orig);
        else{
        command_execute(orig);
        }//
        
	

}



