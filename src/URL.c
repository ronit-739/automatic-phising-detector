#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_URL_LENGTH 100
void extract_protocol(const char *url, char *protocol)
{
    while (*url != '\0')
    {
        if (url[0] == '/' && url[1] == '/')
        {
            break;
        }
        *protocol = *url;
        url++;
        protocol++;
    }
    *protocol = '\0';
}

void extract_sub_domain_and_domain_and_tldomain(const char *url, char *sub_domain, char *domain, char *tl_domain)
{
    const char *start = strstr(url, "://");
    if (start != NULL)
    {
        start = start + 3;
    }
    strncpy(sub_domain, start, 3);
    sub_domain[3] = '\0';
    start += 4;
    char *mid = strchr(start, '.');
    if (mid != NULL)
    {
        strncpy(domain, start, mid - start);
        domain[mid - start] = '\0';
    }
    else
    {
        strcpy(domain, start);
    }
    char *end = strchr(start, '/');
    if (end != NULL)
    {
        strncpy(tl_domain, mid, end - mid);
        tl_domain[end - mid] = '\0';
    }
    else
    {
        strcpy(tl_domain, mid);
    }
}
