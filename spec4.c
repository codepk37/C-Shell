#include "header.h"
char* get_home(){  //getenv("HOME") replacement
	struct passwd *pw = getpwuid(getuid());
	char *homedir = pw->pw_dir;
	return homedir;
}
//    home should start with :  /home/popos/OSN  i.e. atart with slash '/'

/*
//Colouring Code  : 	BLUE + GREEN + WHITE
void colored_ls(const char *path) {
    char command[100];
    snprintf(command, sizeof(command), "ls --color=auto %s", path);
    system(command);
}

int main() {
    char user_input[100];

    while (1) {
        printf("%s> ", getcwd(NULL, 0));
        fgets(user_input, sizeof(user_input), stdin);
        user_input[strcspn(user_input, "\n")] = '\0'; // Remove the newline character

        if (strcmp(user_input, "exit") == 0) {
            break;
        }

        colored_ls(user_input);
    }

    return 0;
}
*/


/*
INPUT FORMAT :peek -l <path/name>    -> change to path + ls -l

works in our program:  system(comm)   /also in lexicographic order
ls 
ls -l
ls -a 
ls -a -l 
ls -l -a 
ls -la 
ls -al 

just used: peek -> ls 

(Use path made from Spec3.c)
Similar to warp, you are expected to support “.”, “..”, “~”, and “-” symbols
Support relative and absolute paths.


NO multiple Arguments*
Use specific color coding (there small code following it)
*/

//    ls -l

void print_permissions(mode_t mode) {    //file type and permissions
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}


int give_file_type(mode_t mode) { //return,file_type executable ,directory ..
    if (S_ISDIR(mode)) {
         return 1; // Blue for directories
    } else if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH) {
         return 2; // Green for executables
    } else {
         return 3; // White for other files
    }
}
char * lower(const char *ar){  //sometimes memory fails
	char *st=malloc (strlen(ar)*sizeof(char));  //coz cannot return local var ,therefore dynamic memory
	for(int i=0;i<strlen(ar);i++){
		if(ar[i]<='Z' && ar[i]>='A'){
		    char ch=ar[i]-'A'+'a';
			//
			st[i]=ch;
			
		}
		else{
			st[i]=ar[i]; 
		}
	}
	return st;
	
}

int compare_entries(const struct dirent **a, const struct dirent **b) {
	//USE WHEN MEMORY FAILS
    //return strcmp(((*a)->d_name),((*b)->d_name));  // make all lower case and compare ;else F < c
    char *pt1=NULL,*pt2=NULL; 
    int ans= strcmp(pt1=lower((*a)->d_name),pt2=lower((*b)->d_name));
    free(pt1);
    free(pt2);
    return ans;
}

void ls_info(char * path,int hide,int full){
	DIR *dir = opendir(path);

    if (dir) { 
        struct dirent **entries;
        int num_entries = scandir(path, &entries, NULL, compare_entries);

        if (num_entries < 0) {
            perror("Error scanning directory");
            return ;
        }

        for (int i = 0; i < num_entries; ++i) {
            struct dirent *entry = entries[i];

            // Skip hidden files
            if(hide && entry->d_name[0] == '.') {
                free(entry);
                continue;
            }

            struct stat file_stat;
            char full_path[PATH_MAX]; //
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
		
	    //printf("fullpath:%s\n",full_path);  //path of files in given directory
            if (stat(full_path, &file_stat) == 0) {
                struct passwd *user_info = getpwuid(file_stat.st_uid);
                struct group *group_info = getgrgid(file_stat.st_gid);
                char time_str[20];
                strftime(time_str, sizeof(time_str), "%b %d %H:%M",localtime(&file_stat.st_mtime));
		
		
		if(full)
			{     //displays extra information
		        print_permissions(file_stat.st_mode);
		        printf(" %2lu %s %s %6lld %s ",
		               file_stat.st_nlink,
		               user_info->pw_name,
		               group_info->gr_name,
		               (long long)file_stat.st_size,
		               time_str);             
		        }
		        mode_t  mode=file_stat.st_mode;
		        char *name=entry->d_name;
		        if (S_ISDIR(mode)) {
				printf("\033[1;34m%s\033[0m\n", name); // Blue for directories
			 }
			  else if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH) {
				printf("\033[1;32m%s\033[0m\n", name); // Green for executables
			 }
			   else {
				printf("\033[1;37m%s\033[0m\n", name); // White for other files
			 }
		        //printf(entry->d_name)
                
                }
                
                else{  //only print filename's
                	char *name=entry->d_name;
                	mode_t mode=file_stat.st_mode;
		        if (S_ISDIR(mode)) {
				printf("\033[1;34m%s\033[0m\n", name); // Blue for directories
			 }
			  else if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH) {
				printf("\033[1;32m%s\033[0m\n", name); // Green for executables
			 }
			   else {
				printf("\033[1;37m%s\033[0m\n", name); // White for other files
			 }
                	
                }
            
            
            free(entry);
        }
        
        free(entries);
        closedir(dir);
    } else {
        perror("Error opening directory");
        return ;
    }

}

void execute_ls(char* input){
	char comm[100];//   ls <flag> <path> 
        strcpy(comm,input);
        
        //////////  ls -  error handling
        int flag=0;
	for(int i=0;i<strlen(comm);i++){
	    	if(comm[i]=='-'){
	    		flag=1;
	    	}
	    	else if(flag==1 && (comm[i]=='l' || comm[i]=='a')){
	    		flag=0;
	    	}
	    	else if(flag==1 ){
	    		break;
	    	}
	}
	if(flag==1){printf("ls : cannot access '-': No such file or directory\n");return;}
        ///////////
        
                
        int l=0;
        int a=0;
        
        if(strstr(comm,"-a")!=NULL){a=1;}
        if(strstr(comm,"-l")!=NULL){l=1;}
        if(strstr(comm,"-al")!=NULL){a=1;l=1;}
        if(strstr(comm,"-la")!=NULL){a=1;l=1;}
        
        //   //////////////////path starting with '/'  or '.'  or  '~' or  relative
     	size_t path_length = 0;
	char path[100];   
	char calculated_path[100]; // Create a separate string to build the path
	int flag2=0;
	for (int i = 0; i <=strlen(comm); i++) {
	    if (flag2 == 1 || comm[i] == '/' || comm[i] == '.' || comm[i] == '~') {
		flag2 = 1;
		calculated_path[path_length] = comm[i]; // Append to calculated_path
        	path_length++; 
		//strncat(calculated_path, &comm[i], 1); // Append to calculated_path
	    }
	}
	if (strlen(calculated_path) > 0 && calculated_path[strlen(calculated_path) - 1] == '\n') {
	    calculated_path[strlen(calculated_path) - 1] = '\0';
	}
	
	strcpy(path, calculated_path);
	   // printf("comm:%s path : %s\n",comm,path);
        //////////
        //size =0 also for no symbol
        
        char *home = get_home();
        char cwd[200];
        if (getcwd(cwd, sizeof(cwd)) == NULL) { //cwd
        	perror("getcwd peek: spec4");
        	exit(EXIT_FAILURE);
    	}
    	
        if(strstr(path,"..")!=NULL){ //parent path of cwd
        	strcpy(path,dirname(strdup(cwd)));
        	
        }        
        else if(strstr(path,".")!=NULL){  //cwd
        	strcpy(path,cwd);
        }
        else if(strstr(path,"~/")!=NULL){ // ~/OSN  absolute path
            	char temp[100];
                snprintf(temp,sizeof(temp),"%s%s", home,path+1);// ~/OSN -> home/OSN
            	strcpy(path,temp);
        }
        
        else if(strstr(path,"~")!=NULL){
        	strcpy(path,get_home());
        }
        else if(strlen(path)==0){
        	strcpy(path,cwd);
        }
        
        ///////////// got path
        
        int full=l;
        int hide=1-a;
        
        //printf("path: %s  hide:%d full:%d\n",path,hide,full);
              
        ls_info(path,hide,full);
        
        
}

/*
int main() {
    char *path = "/home/popos/OSN/"; // Replace with the actual path
    int hide =0;s
    int full =0;
    ls_info(path,hide,full);
    return 0;
}
*/
