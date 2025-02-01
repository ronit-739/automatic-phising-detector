#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>  

void extract_domain(char *url, char *domain) {
    char *start = url;

    if (strncmp(url, "http://", 7) == 0) {
        start += 7;
    } else if (strncmp(url, "https://", 8) == 0) {
        start += 8;
    }

    char *end = strchr(start, '/');
    if (end != NULL) {
        *end = '\0';  
    }

    strcpy(domain, start);
}

void url_decode(char *src, char *dest) {
    while (*src) {
        if (*src == '%' && isxdigit(*(src + 1)) && isxdigit(*(src + 2))) {
            char hex[3] = {src[1], src[2], '\0'};
            *dest++ = (char)strtol(hex, NULL, 16);
            src += 3;
        } else {
            *dest++ = *src++;
        }
    }
    *dest = '\0';
}

int keywordcontent(char *text, const char *keywords[], int numkeywords) {
    for (int i = 0; i < numkeywords; i++) {
        if (strstr(text, keywords[i]) != NULL) {
            return 1; 
        }
    }
    return 0;
}

int is_punycode_encoded(char *domain) {
    return (strstr(domain, "xn--") != NULL);
}
