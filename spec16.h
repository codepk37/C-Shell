#ifndef __SPEC16_H
#define __SPEC16_H


void sendHttpGetRequest(int sockfd, const char *url);
void extractAndPrintText(const char *htmlContent) ;
int iMan_comm(const char *command) ;


#endif
