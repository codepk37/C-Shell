#ifndef __SPEC12_H
#define __SPEC12_H

struct ProcessInfo {
    int pid;
    char state;
    char cmd[256];
};
int compareByCmdName(const void *a, const void *b) ;
void activities() ;

#endif
