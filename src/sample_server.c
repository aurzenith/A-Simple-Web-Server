#include <stdio.h>
#include <string.h>

// these are for Linux OSs, require dev-tools I'll make a thing for WSL support
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <assert.h>






int main(int argc, char* argv[]) 
{

    // most of the functions will return an error number -1 if failed
    int errorValue;

    // struct to hold all info of our ip port etc.. hints is used to construct certain parts of it as well
    struct addrinfo hints, *servInfo;

    // manually inputted, but you can change to grab from console 
    char* ipAddr = "127.0.0.1";

    // where we store sockets we create aka (client ip, serv ip, ports)
    struct sockaddr_storage client_addr;
    socklen_t addr_size;

    //printable stuff, sockaddr_in is the actual struct of the ip address itself
    struct sockaddr_in* ipv4;
    char* ipver;
    void* addr;
    char ipstr[INET_ADDRSTRLEN];
    
    // for reading from recv()
    char buff[2048];
    memset(buff, 0, sizeof(buff));

    const char* message = { "HTTP/1.1 200 OK\r\nContent-Type: text/html;" 
        "charset=UTF-8\r\n"
        "Content-Length: 256\r\nConnection: Close\r\n"
        "Cache-Control: no-cache\r\n"
        "<!DOCTYPE HTML><body><p>HELLO</p></body>"
    };

    // set hints up
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;


    // check for an error while we input into the addrinfo struct
    if ((errorValue = getaddrinfo(ipAddr, "9696", &hints, &servInfo)) != 0) {
        fprintf(stderr, "getaddinfo: %s\n", gai_strerror(errorValue));
        return 1;
    }

    // write info back our displayable things
    ipv4 = (struct sockaddr_in *)servInfo->ai_addr;
    addr = &(ipv4->sin_addr);
    ipver = "IPv4";

    // change the format from n(etwork)top(rintable)
    inet_ntop(servInfo->ai_family, addr, ipstr, sizeof(ipstr));

    printf(" %s: %s\n", ipver, ipstr);

    // open connection for webserv

    // fill descriptors, aka hold data about the socket
    int sockfd, newfd;

    // created the socketfd
    sockfd = socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol);

    // bind to address and port etc and listen
    bind(sockfd, servInfo->ai_addr, servInfo->ai_addrlen);
    // 5 means it will backlog up to 5 requests to connect at a time
    listen(sockfd, 5);

    addr_size = sizeof(client_addr);

    // accept the connection and put it in the other socketfd
    newfd = accept(sockfd, (struct sockaddr*) &client_addr, &addr_size);

    // receive data and put it in a string
    recv(newfd, buff, 2048, 0);

    send(newfd, message, 2048, 0);


    printf("%s", buff);


    // clean up
    freeaddrinfo(servInfo);

    return 0;
}