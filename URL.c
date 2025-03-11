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

void extract_sub_domain_and_domain(const char *url, char *sub_domain, char *domain)
{
    const char *start = strstr(url, "://");
    if (start != NULL)
    {
        start = start + 3;
    }
    while (*start != '.')
    {
        *sub_domain = *start;
        start++;
        sub_domain++;
    }
    start++;
    const char *end = strchr(start, '/');
    if (end != NULL)
    {
        strncpy(domain, start, end - start);
        domain[end - start] = '\0';
    }
    else
    {
        strcpy(domain, start);
    }
}
