#include <stdio.h>
#include <string.h>
int edit_distance(char[], char[]);
int min_length(int, int, int);

int main()
{

    char word1[100], word2[100];
    int ld;
    printf("Enter first string:\n");
    scanf("%s", word1);
    printf("Enter second string:\n");
    scanf("%s", word2);

    ld = edit_distance(word1, word2);
    printf("Levenshtein distance: %d\n", ld);
    if (ld <= 3)
    {
        printf("suspecious!!");
    }
    else
    {
        printf("doesnot look suspecious!");
    }

    return 0;
}
int min_length(int x, int y, int z)
{
    if (x < y && x < z)
    {
        return x;
    }
    if (y < z)
    {
        return y;
    }
    else
    {
        return z;
    }
}
int edit_distance(char string1[], char string2[])
{
    int i, j;
    int l1 = strlen(string1);
    int l2 = strlen(string2);
    int matrix[l1 + 1][l2 + 1];

    for (i = 0; i <= l1; i++)
    {
        matrix[i][0] = i;
    }

    for (j = 0; j <= l2; j++)
    {
        matrix[0][j] = j;
    }

    for (i = 1; i <= l1; i++)
    {
        for (j = 1; j <=l2; j++)
        {
            if (string1[i - 1] == string2[j - 1])
            {
                matrix[i][j] = matrix[i - 1][j - 1];
            }
            else
            {

                matrix[i][j] = 1 + min_length(matrix[i - 1][j - 1], matrix[i- 1][j], matrix[i][j - 1]);
            }
        }
    }
    return matrix[l1][l2];
}