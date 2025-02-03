#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "levenshtein.h"

int min_length(int x, int y, int z) {
    if (x < y && x < z) {
        return x;
    }
    if (y < z) {
        return y;
    } else {
        return z;
    }
}




int edit_distance(char string1[100], char string2[100]) {
    int i, j;
    int l1 = strlen(string1);
    int l2 = strlen(string2);
    int matrix[l1 + 1][l2 + 1];

    // Initialize the matrix with base cases
    for (i = 0; i <= l1; i++) {
        matrix[i][0] = i;
    }

    for (j = 0; j <= l2; j++) {
        matrix[0][j] = j;
    }

    // Fill the matrix with Levenshtein distance calculation
    for (i = 1; i <= l1; i++) {
        for (j = 1; j <= l2; j++) {
            if (string1[i - 1] == string2[j - 1]) {
                matrix[i][j] = matrix[i - 1][j - 1];
            } else {
                matrix[i][j] = 1 + min_length(matrix[i - 1][j - 1], matrix[i - 1][j], matrix[i][j - 1]);
            }
        }
    }
    return matrix[l1][l2];  // Return the Levenshtein distance
}

 struct result check_edit_distance(char word1[]) {
    struct result res;
    res.ld = 100;  
    res.matching_url[0] = '\0';  // Initialize empty string

    FILE *fp = fopen("safe_url.txt", "r");  
    if (!fp) {
        printf("Error: safe_url.txt not found\n");
        return res;
    }

    char safe_domain[100];  
    while (fscanf(fp, "%s", safe_domain) != EOF) {
        int distance = edit_distance(word1, safe_domain);
        if (distance < res.ld) {
            res.ld = distance;
            strcpy(res.matching_url, safe_domain);
        }
    }
    fclose(fp);
    return res;
}



