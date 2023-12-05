


/* Conclusion Spec ---3
warp test -> cd test 
warp Copies -> cd Copies  
warp      ->(only   cd ==> cd ~)   No Args passed
warp .    -> cd .    = remain in the current directory, refeshing it ,wont move anywhere
warp ~    -> cd ~    = /home/popos  (or refers to home directory of shell)
warp -    -> cd -    = last pwd executed (only 2 pair as history)
warp ..   -> cd ..   = move to the parent directory of current directory

cd /       ->     root directory is the first directory in your filesystem hierarchy. 

Absolute path : cd /home/popos/OSN/Copies  ,directly changes from any place(**)
Relative path : cd dir_1/dir_2/dir_3       ,between folder relative

e.x.    <JohnDoe@SYS:~/test/tutorial> warp ~/project
	/home/johndoe/project
	<JohnDoe@SYS:~/project>

Execute warp sequentially :implement ,not direct as ,cd Accepts 1 command
<JohnDoe@SYS:~/test/assignment> warp .. tutorial
/home/johndoe/test
/home/johndoe/test/tutorial

 The first code is without the root directory (/) and the second code is with the root directory (/).
 chdir() is a system function. This means that it uses the absolute paths. If the Linux home directory (/) is not specified as the start of the path.
 ";
 */
 


/*void main3(){
	char cwd[256];
	 if (getcwd(cwd, sizeof(cwd)) == NULL)
	      perror("getcwd() error\n");
	    else
	      printf("current working directory is: %s\n", cwd);

	char pa[]=".. \n"; // or char *pa
	int ch=chdir(pa);
	if(ch<0)    //-1
	    printf("chdir change of directory not successful\n");
	 else    //0
	    printf("chdir change of directory successful\n");
	    
	  if (getcwd(cwd, sizeof(cwd)) == NULL)
	      perror("getcwd() error\n");
	   else
	      printf("current working directory is: %s\n", cwd);
	  
	  printf("getenv  %d", strlen(getenv("HOME")));
	  
	

	  printf(" homedir %d",strlen(gethome()));

}
*/

