#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

struct result {
    int ld;
    char matching_url[100];
};

int edit_distance(char[100], char[100]);
int min_length(int, int, int);
struct result check_edit_distance(char[100]);

#endif
