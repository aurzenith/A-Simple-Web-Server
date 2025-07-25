#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <malloc.h>

#define HTTP_HEADER_MAX_SIZE 1024
#define HTTP_RESPONSE_MAX_SIZE 10000


enum http_signal {
    HTTP_200_OK,
    HTTP_404_NOT_FOUND,
    HTTP_500_INTERNAL_SERVER_ERROR
};




void printAddressesInfo(struct addrinfo* addressInfo);

char* createHtmlResponse(enum http_signal currentSignal, char* htmlContent, int contentSize);



#endif