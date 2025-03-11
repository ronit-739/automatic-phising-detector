#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
void url_decode(char *src, char *dest, int *sus)
{
    while (*src)
    {
        if (*src == '%' && isxdigit(*(src + 1)) && isxdigit(*(src + 2)))
        {
            *sus += 1;
            char hex[3] = {src[1], src[2], '\0'};
            *dest++ = (char)strtol(hex, NULL, 16);
            src += 3;
        }
        else
        {
            *dest++ = *src++;
        }
    }
    *dest = '\0';
}

int keywordcontent(char *text, char **keywords, int numkeywords, int *sus)
{
    for (int i = 0; i < numkeywords; i++)
    {
        if (strstr(text, keywords[i]))
        {
            *sus += 1;
        }
    }
}

int is_punycode_encoded(char *domain, int *sus)
{
    if (strstr(domain, "xn--") != NULL)
    {
        *sus += 3;
    }
}

void filter_special_chars(char *str, const char *special_chars, int *sus)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (strchr(special_chars, str[i]))
        {
            *sus += 1;
        }
    }
}

int read_keywords_from_file(const char *filename, char ***keywords)
{
    FILE *file = fopen(filename, "r");
    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file))
    {
        count++;
    }

    *keywords = (char **)malloc(count * sizeof(char *));
    rewind(file);

    int index = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        (*keywords)[index] = strdup(buffer);
        index++;
    }

    fclose(file);
    return count;
}

int siteCheck(char domain[200])
{
    int sus = 0;
    char decoded_domain[200];
    char **keywords;
    int num = read_keywords_from_file("keywords.txt", &keywords);
    url_decode(domain, decoded_domain, &sus);
    filter_special_chars(decoded_domain, "@#$%^&*()+=-[]\\\';,/{}|\":<>?~_", &sus);
    is_punycode_encoded(decoded_domain, &sus);
    keywordcontent(decoded_domain, keywords, num, &sus);
    for (int i = 0; i < num; i++)
    {
        free(keywords[i]);
    }
    free(keywords);
    return sus;
}