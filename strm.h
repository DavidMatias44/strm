#ifndef STRM_H
#define STRM_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int table[26] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void print_usage();
void transform(char **s, const bool remove_vowels_flag, const bool remove_duplicates_flag);
void remove_non_alpha(char **src, size_t *size);
void count_vowels();
void remove_vowels(char **s, size_t *size);
void count_duplicates(char *s, const size_t size);
void remove_duplicates(char **s, size_t size);
int save_in_file(char* s, const char *file_name);
int table_at(const char c);
void print_table();
int compare(const void *a, const void *b);

#endif // STRM_H

#ifdef STRM_H_IMPLEMENTATION

void print_usage()
{
    printf("Usage: main <string>\n");
    printf("-v\t main -v <string>   \t\t\t remove vowels\n");
    printf("-d\t main -d <string>   \t\t\t remove duplicates\n");
    printf("-s\t main -s <string>   \t\t\t sort the output string\n");
    printf("-o\t main -o <file-name> <string>   \t save output string into file\n");
}

void transform(char **s, bool remove_vowels_flag, bool remove_duplicates_flag)
{
    size_t s_len = strlen(*s);

    remove_non_alpha(s, &s_len);

    if (remove_vowels_flag) {
        count_vowels();
        remove_vowels(s, &s_len);
    }

    if (remove_duplicates_flag) {
        count_duplicates(*s, s_len);
        remove_duplicates(s, s_len);
    }
}

void remove_non_alpha(char **src, size_t *size)
{
    char *aux = (char *)malloc(sizeof(char)*(*size) + 1);
    size_t count = 0;
    for (size_t i = 0; i < *size; ++i) {
        char c = (*src)[i];
        if (isalpha(c)) {
            aux[count++] = c;
        }
    }
    aux[count] = '\0';
    *size = count;
    strcpy(*src, aux);
    free(aux);
}

void count_vowels()
{
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    for (size_t i = 0; i < 5; ++i) {
        table[vowels[i] - 97] = 2;
    }
}

void remove_vowels(char **s, size_t *size)
{
    char *aux = (char *)malloc(sizeof(char)*(*size) + 1);
    size_t count = 0;
    for (size_t i = 0; i < *size; ++i) {
        char c = (*s)[i];
        if (table_at(c) < 2) {
            aux[count++] = c;
        }
    }
    aux[count] = '\0';
    *size = count;
    strcpy(*s, aux);
    free(aux);
}

void count_duplicates(char *s, const size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        char c = s[i];
        if (isupper(c)) {
            c += 32; 
        }

        table[c - 97]++;
    }
}

void remove_duplicates(char **s, size_t size)
{
    char *aux = (char *)malloc(sizeof(char)*size + 1);
    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        char c = (*s)[i];
        if (table_at(c) < 2) {
            aux[count++] = c;
        }
    }
    aux[count] = '\0';
    strcpy(*s, aux);
    free(aux);
}

int save_in_file(char* s, const char *file_name)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL) return 1;

    size_t s_len = strlen(s) + 1;
    sprintf(s, "%s\n", s);
    size_t bytes_written = fwrite(s, sizeof(char), s_len, file);
    if (s_len != bytes_written) return 1;

    return 0;

}

int table_at(const char c)
{
    if (c < 97) return table[c + 32 - 97];
    return table[c - 97];
}

void print_table()
{
    int aux = 97;
    for (size_t i = 0; i < 26; ++i) {
        printf("%c:%d ", aux++, table[i]);
    }
    printf("\n");
}

int compare(const void *a, const void *b)
{
    return *((char *)a) - *((char *)b);
}

#endif // STRM_H_IMPLEMENTATION

