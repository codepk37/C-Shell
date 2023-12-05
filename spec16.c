#include "header.h"

//Competed using TCP and DNS 

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <regex.h>*/

// Function to send an HTTP GET request
void sendHttpGetRequest(int sockfd, const char *url) {
    char request[4096]; // Adjust the buffer size as needed

    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nHost: man.he.net\r\n\r\n", url);
    // HTTP GET request string using the provided url,
    //HTTP version (HTTP/1.1)
    write(sockfd, request, strlen(request));
}


// Function to extract and print text content using regular expressions
void extractAndPrintText(const char *htmlContent) {
    regex_t regex;
    regmatch_t matches[1];

    // Define a regular expression pattern to match text within HTML tags
    const char *pattern = ">([^<]+)<";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regular expression\n");
        return;
    }

    const char *cursor = htmlContent;

    while (regexec(&regex, cursor, 1, matches, 0) == 0) {
        // Print the matched text
        printf("%.*s\n", (int)(matches[0].rm_eo - matches[0].rm_so - 2), cursor + matches[0].rm_so + 1);

        // Move the cursor to the next position
        cursor += matches[0].rm_eo;
    }

    regfree(&regex);
}

int iMan_comm(const char *command) {
    char input[strlen(command) + 1]; // Remove iMan
    strcpy(input, command);

    strtok(input, " \n"); // iMan
    char *temp = strtok(NULL, " \n"); // sleep or ls or echo  ...
    char inp[100];
    strcpy(inp, temp);

    char url[1024]; // Adjust the buffer size as needed
    snprintf(url, sizeof(url), "http://man.he.net/?topic=iMan+%s&section=all", inp);
    printf("URL: %s\n", url);


    // DNS Resolution:
    //DNS resolution, which is the process of converting a human-readable domain name (e.g., "man.he.net") into an IP address 
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));// initially set to zero 
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; //TCP 

    int addr_result = getaddrinfo("man.he.net", "80", &hints, &res);
    if (addr_result != 0) {       //hostname ,http service
        fprintf(stderr, "DNS resolution failed: %s\n", gai_strerror(addr_result));
        return 1;
    }
    //Got:IP of hostname stored in res


    // Open a TCP Socket
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);//integer: socket file descriptor
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Connect to the Server
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("Socket connection failed");
        close(sockfd);
        return 1;
    }

    // Send an HTTP GET Request
    sendHttpGetRequest(sockfd, url);

    // Read the HTML Response
    char buffer[1024]; // Adjust the buffer size as needed
    ssize_t bytes_read;
    char *htmlContent = NULL;
    size_t htmlSize = 0;

    while ((bytes_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
        // Resize the htmlContent buffer
        htmlContent = realloc(htmlContent, htmlSize + bytes_read + 1);
        		                 //original  + read curr
        if (htmlContent == NULL) {
            perror("Memory allocation failed");
            close(sockfd);
            return 1;
        }

        // Copy the new data into htmlContent
        memcpy(htmlContent + htmlSize, buffer, bytes_read);
        //          Pointer+Size pe   buffer put
        htmlSize += bytes_read;
        htmlContent[htmlSize] = '\0';
    }

    // Extract and Print Text Content
    extractAndPrintText(htmlContent);

    // Clean up
    free(htmlContent);
    close(sockfd);

    return 0;
}

//SERVER: socket ,bind  , listen , accept , send-receive
//CLIENT: socket ,       ,connect,        , send-receive


