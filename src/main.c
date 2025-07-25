#include "web_server.h"
// most of the functions will return an error number -1 if failed
    


int main(int argc, char** argv) {
    int errorValue;
    struct addrinfo hints, *servInfo;
    char buff[2048];
    char* http_response;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;


    // will be replaced with file
    char html_content[] = { 
        "<!DOCTYPE HTML>"
        "<body>"
        "<p>HELLO</p>"
        "</body>"
    };


    // manually inputted for now,
    char* ipAddr = "127.0.0.1";
    struct sockaddr_storage client_addr;
    socklen_t addr_size;
    int servsockfd, clientsockfd;


    char* port = "8080";



    if ((errorValue = getaddrinfo(ipAddr, port, &hints, &servInfo)) != 0) {
        fprintf(stderr, "getaddinfo: %s\n", gai_strerror(errorValue));
        return 1;
    }

    printAddressesInfo(servInfo);

    servsockfd = socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol);

    bind(servsockfd, servInfo->ai_addr, servInfo->ai_addrlen);
    listen(servsockfd, 10);

    addr_size = sizeof(client_addr);

    http_response = createHtmlResponse(HTTP_200_OK, html_content, strlen(html_content)); 
    if (http_response == NULL) {
        fprintf(stderr, "Failed to create HTTP response. Exiting.\n");
        return 4;
    }

    while(1) {
        clientsockfd = accept(servsockfd, (struct sockaddr*) &client_addr, &addr_size);
        recv(clientsockfd, buff, 2048, 0);
        printf("%s", buff);
        
        send(clientsockfd, http_response, strlen(http_response), 0);


        // logging will create actual logging file stuff later...
  
    }

    free(http_response);
    freeaddrinfo(servInfo);
    return 0;
}