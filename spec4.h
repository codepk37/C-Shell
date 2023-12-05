#ifndef __SPEC4_H
#define __SPEC4_H

char* get_home();
void print_permissions(mode_t mode);
int give_file_type(mode_t mode) ;
char * lower(const char *ar);
int compare_entries(const struct dirent **a, const struct dirent **b) ;
void ls_info(char * path,int hide,int full);
void execute_ls(char* input);

#endif
