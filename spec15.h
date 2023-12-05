#ifndef __SPEC15_H
#define __SPEC15_H


int getOwnPID();
int isNumber(const char *str);
void die(const char *s) ;
//struct termios orig_termios;
void disableRawMode() ;
void enableRawMode();
int getnum(char*p);   //from spec14
int neonate(char * command);


#endif
