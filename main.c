#include <stdio.h>
#include "levenshtein.c"
#include "blacklist.c"
#include "URL.c"
#include "ApiCheck.c"
#include "keywordfilter.c"

int main()
{
    float count = 0;
    char url[MAX_URL_LENGTH];
    char protocol[10];
    char sub_domain[5];
    char domain[200];
    char alldomain[200];
    char tl_domain[10];
    char web[200];
    float percentage = 30;
    const char *api_key = "AIzaSyCMqA6MwJ1e22meqSOKkISdtZIte9u7psA";
    int sus = 0;
    printf("Enter a URL: ");
    scanf("%s", url);
    extract_protocol(url, protocol);
    extract_sub_domain_and_domain_and_tldomain(url, sub_domain, domain, tl_domain);
    strcpy(alldomain, domain);
    strcat(alldomain, tl_domain);
    if (strcmp(protocol, "https:") != 0)
    {
        count += 0.4;
    }
    if (strcmp(sub_domain, "www") != 0)
    {
        count += 0.6;
    }
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
        count += 1.2;
    }
    else
    {
        printf("Does not look suspicious.\n");
    }

    printf("\n\n------------Second Test------------\n");
    if (!isBlacklisted(alldomain))
    {
        printf("URL is NOT in our blacklist\n");
    }
    else
    {
        printf("URL is in our blacklist!\n");
        count += 1.5;
    }

    printf("\n\n------------Third Test------------\n");
    if (check_phishing_site(url, api_key))
    {
        count += 1.8;
        printf("URL is blacklisted by google.\n");
    }
    else
    {
        printf("URL is not blacklisted by google\n");
    }

    printf("\n\n------------Fourth Test------------\n");
    sus = siteCheck(domain);
    if (sus > 3)
    {
        printf("Potential fraud site");
        count += 1.5;
    }
    else
    {
        printf("Safe site");
    }
    printf("\n\n---------------------------------------------");
    percentage = (float)count / 7 * 100;

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
    printf("\nUnsafe percentage: %.2f %% \n ", percentage);
    if (percentage > 20)
    {
        FILE *fp = fopen("blacklists.txt", "a+");
        while (fscanf(fp, "%s", web) != EOF)
        {
            if (strcmp(web, alldomain) == 0)
            {
                return 0;
            }
        }
        fprintf(fp, "\n%s", alldomain);
        fclose(fp);
    }
    return 0;
}