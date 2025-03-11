#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_URL_LENGTH 30

void convert_to_lowercase(char *url) {
    for (int i = 0; url[i] != '\0'; i++) {
        url[i] = tolower(url[i]);
    }
}

void check_security(const char *url) {
    char rem[MAX_URL_LENGTH];

    if (strlen(url) >= MAX_URL_LENGTH) {
        printf("URL is unsecure: Too long\n");
        return;
    }

    if (strncmp(url, "https://", 8) == 0) {
        printf("URL is secure: HTTPS\n");
    } else if (strncmp(url, "http://", 7) == 0) {
        printf("URL is unsecure: HTTP\n");
    } else {
        printf("URL is unsecure: Unknown protocol\n");
        return;
    }

    const char *w = strstr(url, "www.");
    if (w != NULL) {
        const char *com = strstr(w, ".com");
        if (com != NULL) {
            int len = com - (w + 4);
            if (len >= MAX_URL_LENGTH - 1) {
                len = MAX_URL_LENGTH - 1;
            }
            strncpy(rem, w + 4, len);
            rem[len] = '\0';

            printf(" %s\n", rem);
        } else {
            printf("URL contains 'www.', but no '.com' found after 'www.'\n");
        }
    } else {
        printf("URL does not contain 'www.'\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];

    printf("Enter a URL: ");
    scanf("%s", url);

    convert_to_lowercase(url);
    check_security(url);

    return 0;
}