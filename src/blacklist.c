
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_strings(const void *a, const void *b)
{
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}
int binary_search_blacklist(char *list[], int size, const char *target)
{
    int left = 0, right = size - 1, mid;

    while (left <= right)
    {
        mid = (left + right) / 2;
        int cmp = strcmp(list[mid], target);

        if (cmp == 0)
            return 1;
        if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return 0;
}

int isBlacklisted(const char *str)
{
    FILE *file = fopen("blacklists.txt", "r");
    if (!file)
    {
        printf("Error: Could not open blacklist file.\n");
        return 0;
    }
    char *blacklist_urls[1000];
    int count = 0;
    char line[100];
    while (count < 1000 && fscanf(file, "%99s", line) != EOF)
    {
        blacklist_urls[count] = malloc(strlen(line) + 1);
        if (!blacklist_urls[count])
        {
            printf("Memory allocation failed.\n");
            fclose(file);
            return 0;
        }
        strcpy(blacklist_urls[count], line);
        count++;
    }
    fclose(file);
    qsort(blacklist_urls, count, sizeof(char *), compare_strings);
    int result = binary_search_blacklist(blacklist_urls, count, str);
    for (int i = 0; i < count; i++)
    {
        free(blacklist_urls[i]);
    }

    return result;
}
