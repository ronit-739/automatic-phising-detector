#include <stdio.h>
#include <string.h>

int edit_distance(char[], char[]);
int min_length(int, int, int);
struct result check_edit_distance(char[]);
int isBlacklisted(char []);
int checkSuspiciousPatterns(char []);
int checkURLLength(char []);
int checkHTTPS(char[]);
 struct result{
        int ld;
        char matching_url[100];

    };


int main()

 {
   
    char url[100]; 
    int checkpassed=0;
    printf("Enter URL :\n");
    scanf("%s", url);  // Get the input URL
     struct result res=check_edit_distance(url);

     printf("Levenshtein distance: %d\n", res.ld);
    if(res.ld==0)
    {
        printf("given domain name is real\n");
        printf("Matching safe URL: %s\n", res.matching_url);  // Display matching URL
    }
    if (res.ld <= 3 && res.ld>0) {
        printf("Suspicious URL detected!\n");
        printf("Matching safe URL: %s\n",res.matching_url);  // Display matching URL
    } else {
        printf("Does not look suspicious.\n");
    }

     if(!isBlacklisted(url))
     {
        printf("Url is in not blacklist\n");
        checkpassed++;
     }
     else{
        printf("url is in blacklist\n");
     }
     if (!checkSuspiciousPatterns(url)) {
        printf("Check 2: No suspicious patterns detected.\n");
        checkpassed++;
    } else {
        printf("Check 2: Suspicious patterns detected!\n");
    }

    if (checkURLLength(url)) {
        printf("Check 3: URL length is acceptable.\n");
        checkpassed++;
    } else {
        printf("Check 3: URL length is too long!\n");
    }

    if (checkHTTPS(url)) {
        printf("Check 4: HTTPS is present.\n");
        checkpassed++;
    } else {
        printf("Check 4: HTTPS is missing!\n");
    }

  return 0;


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



int edit_distance(char string1[], char string2[]) {
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


int isBlacklisted(char  str[])
{
    FILE *file= fopen("blacklists.txt","r");
    if(!file){
        printf("Error: Could not open blacklist file.");
        return 1;
    }
    char line[500];
    while(fgets(line,sizeof(line),file))
    {
        line[strcspn(line, "\n")]='\0'; // Remove trailing newline
        if(strstr(str,line))
        {
            return 1;
            fclose(file);
        }
    }


}
int checkSuspiciousPatterns(char str[])
{

}
int checkURLLength(char str[])
{

}
int checkHTTPS(char str[])
{

}



