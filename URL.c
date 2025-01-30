#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_URL_LENGTH 1000

int starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void preprocess_url(char *url) {
    char *start = url;
    while (*start == ' ') {
        start++;
    }
    memmove(url, start, strlen(start) + 1);

    int len = strlen(url);
    while (len > 0 && url[len - 1] == ' ') {
        url[len - 1] = '\0';
        len--;
    }

    for (int i = 0; url[i]; i++) {
        url[i] = tolower(url[i]);
    }
}

void extract_protocol(const char *url, char *protocol) {
    if (starts_with(url, "http://")) {
        strcpy(protocol, "http");
    } else if (starts_with(url, "https://")) {
        strcpy(protocol, "https");
    } else {
        strcpy(protocol, "unknown");
    }
}

void extract_domain(const char *url, char *domain) {
    const char *start = strstr(url, "://");
    if (start != NULL) {
        start = start + 3;
    } else {
        start = url;
    }

    const char *end = strchr(start, '/');
    if (end != NULL) {
        strncpy(domain, start, end - start);
        domain[end - start] = '\0';
    } else {
        strcpy(domain, start);
    }
}

void extract_path(const char *url, char *path) {
    const char *start = strstr(url, "://");
    if (start != NULL) {
        start = start + 3;
    } else {
        start = url;
    }

    const char *slash = strchr(start, '/');
    if (slash != NULL) {
        strcpy(path, slash);
    } else {
        strcpy(path, "/");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    char protocol[10];
    char domain[200];
    char path[MAX_URL_LENGTH];

    printf("Enter a URL: ");
    scanf("%s", url);

    preprocess_url(url);

    extract_protocol(url, protocol);
    extract_domain(url, domain);
    extract_path(url, path);

    printf("Preprocessed URL: %s\n", url);
    printf("Protocol: %s\n", protocol);
    printf("Domain: %s\n", domain);
    printf("Path: %s\n", path);

    return 0;
}