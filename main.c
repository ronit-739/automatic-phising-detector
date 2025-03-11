#include <stdio.h>
#include "levenshtein.c"
#include "blacklist.c"
#include "URL.c"
#include "ApiCheck.c"
int count = 0;
int total_function = 2;

int main()
{
    char url[MAX_URL_LENGTH];
    char protocol[10];
    char sub_domain[5];
    char domain[200];
    float percentage = 30;
    const char *api_key = "";
    //   AIzaSyCMqA6MwJ1e22meqSOKkISdtZIte9u7psA
    printf("Enter a URL: ");
    scanf("%s", url);
    extract_protocol(url, protocol);
    extract_sub_domain_and_domain(url, sub_domain, domain);
    struct result res = check_edit_distance(domain);
    printf("\n\n----------First test--------------\n");
    printf("Levenshtein distance: %d\n", res.ld);

    if (res.ld == 0)
    {
        printf("Given domain name is real\n");
        printf("Matching safe URL: %s\n", res.matching_url);
    }
    else if (res.ld <= 3)
    {
        printf("Suspicious URL detected!\n");
        printf("Matching safe URL: %s\n", res.matching_url);
        count++;
    }
    else
    {
        printf("Does not look suspicious.\n");
    }

    printf("\n\n------------Second Test------------\n");
    if (!isBlacklisted(domain))
    {
        printf("URL is NOT in the blacklist\n");
    }
    else
    {
        printf("URL is in the blacklist!\n");
        count++;
    }

    printf("\n\n------------Third Test------------\n");
    if (check_phishing_site(url, api_key))
    {
        count++;
        printf("URL is blacklisted by google.\n");
    }
    else
    {
        printf("URL is not blacklisted by google\n");
    }
    percentage = (float)count / total_function * 100;

    if (percentage > 0 && percentage <= 30)
    {
        printf("\nsafe!!\n");
    }

    if (percentage >= 31 && percentage <= 60)
    {
        printf("\nSuspecious!!\n");
    }

    if (percentage >= 61 && percentage <= 100)
    {
        printf("\nHigh Risk\n");
    }
    printf("---------------------------------------------");
    printf("\ngiven url has  %.2f %% chance of being a phising url\n ", percentage);

    return 0;
}