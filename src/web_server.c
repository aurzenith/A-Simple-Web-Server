#include "web_server.h"

void printAddressesInfo(struct addrinfo* addressInfo)
{
    // this function needs very few changes for it to be functional with ipv6 (maybe later)
    struct sockaddr_in* ipv4;
    char* ipVer;
    void* ipv4Address;
    char ipstr[INET_ADDRSTRLEN];


    ipv4 = (struct sockaddr_in *)addressInfo->ai_addr;
    ipv4Address = &(ipv4->sin_addr);
    ipVer = "IPv4";

    // change the format from n(etwork)top(rintable)
    inet_ntop(addressInfo->ai_family, ipv4Address, ipstr, sizeof(ipstr));

    printf(" %s: %s\n", ipVer, ipstr);
}

char* createHtmlResponse(enum http_signal currentSignal, char* htmlContent, int contentSize)
{
    char* http_response;
    char http_header_buffer[HTTP_HEADER_MAX_SIZE];
    int total_response_length;


    if (currentSignal == HTTP_200_OK) {
        snprintf(http_header_buffer, sizeof(http_header_buffer),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html;" 
        "charset=UTF-8\r\n"
        "Connection: Close\r\n"
        "Cache-Control: no-cache\r\n"
        "Content-Length: %d\r\n"
        "\r\n", 
        contentSize
        );

    } else {
        fprintf(stderr, "Error Creating HTTP header. Unhandled HTTP signal.\n");
    
        return NULL;
    }

    total_response_length = strlen(http_header_buffer) + contentSize + 1;
    http_response = (char*)malloc(sizeof(char)* (total_response_length));

    if (http_response != NULL) {
        strcpy(http_response, http_header_buffer);
        strcat(http_response,htmlContent);

    } else {
        printf("CREATION FAILED. Memory allocation did not function as expected.");
        return NULL;
    }

    return http_response;
}