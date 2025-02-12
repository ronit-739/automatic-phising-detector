/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "blacklist.h"
int binary_search_blacklist(char list[1000][100], int size, char target[100]);


// Helper function to compare blacklist URLs
int compare_strings(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}


// Binary search function for blacklist URLs
int binary_search_blacklist(char list[1000][100], int size, char target[100]) {
    int left = 0, right = size - 1, mid;

    while (left <= right) {
        mid = (left + right) / 2;
        int cmp = strcmp(list[mid], target);

        if (cmp == 0) return 1; // Match found
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }

    return 0; // Not found in blacklist
}

int isBlacklisted(char str[100]) {
    FILE *file = fopen("blacklists.txt", "r");
    if (!file) {
        printf("Error: Could not open blacklist file.\n");
        return 0;
    }

    // Read all URLs into an array
    char blacklist_urls[1000][100];  // Adjust size as needed
    int count = 0;

    while (fscanf(file, "%s", blacklist_urls[count]) != EOF) {
        count++;
    }
    fclose(file);

    // Sort the blacklist URLs (if not already sorted)
    qsort(blacklist_urls, count, sizeof(blacklist_urls[0]), compare_strings);

    // Use binary search to check if the URL is blacklisted
    return binary_search_blacklist(blacklist_urls, count, str);
}
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Compare function for qsort (corrected for pointers)
int compare_strings(const void *a, const void *b) {
    const char *str1 = *(const char **)a;  // Convert void* to char**
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

// Binary search function for blacklist URLs
int binary_search_blacklist(char *list[], int size, const char *target) {
    int left = 0, right = size - 1, mid;

    while (left <= right) {
        mid = (left + right) / 2;
        int cmp = strcmp(list[mid], target);

        if (cmp == 0) return 1; // Match found
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }

    return 0; // Not found in blacklist
}

int isBlacklisted(const char *str) {
    FILE *file = fopen("blacklists.txt", "r");
    if (!file) {
        printf("Error: Could not open blacklist file.\n");
        return 0;
    }

    // Create an array of pointers
    char *blacklist_urls[1000];
    int count = 0;
    char line[100]; // Temporary buffer to read each URL

    // Read URLs from file and dynamically allocate memory
    while (count < 1000 && fscanf(file, "%99s", line) != EOF)
    /* Reads a word (sequence of non-whitespace characters) from the file.
file is a pointer to the file being read.
"%99s" specifies that up to 99 characters will be read, leaving space for the null terminator (\0) in line.
line is a character array (string) that stores the read input.*/
     {
        blacklist_urls[count] = malloc(strlen(line) + 1);//blacklist_urls[count] is pointer array
        if (!blacklist_urls[count]) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return 0;
        }
        strcpy(blacklist_urls[count], line);
        count++;
    }
    fclose(file);

    // Sort the blacklist URLs
    qsort(blacklist_urls, count, sizeof(char *), compare_strings);

    // Use binary search to check if the URL is blacklisted
    int result = binary_search_blacklist(blacklist_urls, count, str);

    // Free allocated memory
    for (int i = 0; i < count; i++) {
        free(blacklist_urls[i]);
    }

    return result;
}
