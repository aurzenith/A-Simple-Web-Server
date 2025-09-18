

#include "html_reader.h"

char* readHTMLFile(FILE* html_file)
{
    char* buf;
    char* html_content;


    // Get size of file
    fseek(html_file, 0, SEEK_END);
    int size = ftell(html_file);
    rewind(html_file);

    // Allocate buffer to said size
    buf = (char*)malloc(size);

    if (buf == NULL) {
        printf("Could not create buffer, HTMLFILE");
        return NULL;
    }

    html_content = (char*)malloc(size);
    if (html_content == NULL) {
        printf("Could not create buffer, HTMLFILE");
        return NULL;
    }


    // Read each line of the file and concat to html_content
    while (fgets(buf, size, html_file) != NULL) {
        strcat(html_content, buf);
    }

    if (buf == NULL) {
        printf("Error could not read to char*");
        return NULL;
    }

    return html_content;
}