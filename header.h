#include <netdb.h>
#include <arpa/inet.h>
#include <regex.h>
#include <termios.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>  //for PATH_MAX 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <libgen.h> //parent of cwd
//spec3 features

#define MAX_USERNAME_LEN 50
#define MAX_HOSTNAME_LEN 50
#define MAX_PATH_LEN PATH_MAX
#define MAX_INPUT_LENGTH 100
#include <termios.h>

#define MAX_HISTORY_SIZE 15  // Maximum number of recent commands to store
#define MAX_COMMAND_LENGTH 100
#define HISTORY_FILE "command_history.txt"
#define MAX_TOKENS 10 // Maximum number of tokens (adjust as needed)
#define MAX_TOKEN_LENGTH 50 
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
#define MAX_PATH_LENGTH 1024
#define MAX_RESULT_LENGTH 100

#include"solver.h"
#include"spec1.h"
#include"spec2.h"
#include"spec3.h"
#include"spec4.h"
#include"spec5.h"
#include"spec6.h"
#include"spec7.h"
#include"spec8.h"

#include"spec9.h"
#include"spec10.h"
#include"spec11.h"
#include"spec12.h"
#include"spec13.h"
#include"spec14.h"
#include"spec15.h"
#include"spec16.h"

// In header.h
int get_x();
void set_x(int value);


