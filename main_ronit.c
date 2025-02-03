#include <stdio.h>
#include "levenshtein.h"
#include "blacklist.h"

int main() {
    char url[100]; 
    printf("Enter URL:\n");
    scanf("%s", url);

    struct result res = check_edit_distance(url);
    printf("\n\n----------First test--------------\n");
    printf("Levenshtein distance: %d\n", res.ld);

    if (res.ld == 0) {
        printf("Given domain name is real\n");
        printf("Matching safe URL: %s\n", res.matching_url);
    } else if (res.ld <= 3) {
        printf("Suspicious URL detected!\n");
        printf("Matching safe URL: %s\n", res.matching_url);
    } else {
        printf("Does not look suspicious.\n");
    }
   

    printf("\n\n------------Second Test------------\n");
    if (!isBlacklisted(url)) {
        printf("URL is NOT in the blacklist\n");
    } else {
        printf("URL is in the blacklist!\n");
    }

    return 0;
}
