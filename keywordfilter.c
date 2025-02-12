#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>  

// Function to extract domain from a URL
void extract_domain(char *url, char *domain) {
    char *start = url;

    // Remove "http://" or "https://"
    if (strncmp(url, "http://", 7) == 0) {
        start += 7;
    } else if (strncmp(url, "https://", 8) == 0) {
        start += 8;
    }

    // Find the first `/` after domain name
    char *end = strchr(start, '/');
    if (end != NULL) {
        *end = '\0';  // Terminate at first '/'
    }

    // Copy extracted domain to 'domain' variable
    strcpy(domain, start);
}

// Function to decode percent-encoded URLs
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

// Function to check for suspicious keywords
int keywordcontent(char *text, char **keywords, int numkeywords) {
    for (int i = 0; i < numkeywords; i++) {
        if (strstr(text, keywords[i]))
        {
            return 1;  // Found suspicious keyword
        }
    }
    return 0;
}

// Function to check for Punycode-encoded domains
int is_punycode_encoded(char *domain) {
    // Punycode-encoded domains start with "xn--"
    return (strstr(domain, "xn--") != NULL);
}

// Function to filter out special characters (e.g., '@')
void filter_special_chars(char *str, char special_char) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        // If the current character is not the special character, keep it
        if (str[i] != special_char) {
            str[j++] = str[i];
        }
    }
    // Null-terminate the filtered string
    str[j] = '\0';
}

// Function to read keywords from a file
int read_keywords_from_file(const char *filename, char ***keywords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open keywords file");
        return -1;
    }

    // Count the number of keywords
    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        count++;
    }

    // Allocate memory for keywords array
    *keywords = (char **)malloc(count * sizeof(char *));
    if (!*keywords) {
        perror("Failed to allocate memory for keywords");
        fclose(file);
        return -1;
    }

    // Reset file pointer to the beginning
    rewind(file);

    // Read keywords into the array
    int index = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';
        (*keywords)[index] = strdup(buffer);
        if (!(*keywords)[index]) {
            perror("Failed to allocate memory for keyword");
            fclose(file);
            return -1;
        }
        index++;
    }

    fclose(file);
    return count;
}