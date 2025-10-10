/* Kris 2025-07-25*/

#include "html_reader.h"
#include "web_server.h"

int main(int argc, char **argv) {
  int errorValue;
  FILE *html_fptr;
  char *html_file = "../index.html";
  struct addrinfo hints, *servInfo;
  char buff[2048];
  char *http_response;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  html_fptr = fopen(html_file, "r");
  if (html_file == NULL) {
    printf("Error opening file");
    return 1;
  }

  char *html_content = readHTMLFile(html_fptr);
  if (html_content == NULL) {
    printf("Error reading file");
    return 1;
  }

  printf("%s", html_content);

  // manually inputted for now,
  char *ipAddr = "127.0.0.1";
  struct sockaddr_storage client_addr;
  socklen_t addr_size;
  int servsockfd, clientsockfd;

  char *port = "8080";

  // set up addressing in its struct
  if ((errorValue = getaddrinfo(ipAddr, port, &hints, &servInfo)) != 0) {
    fprintf(stderr, "getaddinfo: %s\n", gai_strerror(errorValue));
    return 1;
  }

  printAddressesInfo(servInfo);

  servsockfd =
      socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol);

  errorValue = bind(servsockfd, servInfo->ai_addr, servInfo->ai_addrlen);
  listen(servsockfd, 10);

  addr_size = sizeof(client_addr);

  http_response =
      createHtmlResponse(HTTP_200_OK, html_content, strlen(html_content));
  if (http_response == NULL) {
    fprintf(stderr, "Failed to create HTTP response. Exiting.\n");
    return 4;
  }

  // keep server open for multiple requests
  while (1) {
    clientsockfd =
        accept(servsockfd, (struct sockaddr *)&client_addr, &addr_size);
    recv(clientsockfd, buff, 2048, 0);
    printf("%s", buff);

    send(clientsockfd, http_response, strlen(http_response), 0);

    // logging will create actual logging file stuff later...
  }

  free(http_response);
  fclose(html_fptr);
  free(html_content);
  freeaddrinfo(servInfo);
  return 0;
}
