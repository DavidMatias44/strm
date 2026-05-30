#ifndef STRM_H
#define STRM_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

int table[26] = {0};

void print_usage(void);
void transform(char *s, const bool remove_vowels, const bool remove_duplicates);
void remove_non_alpha(char *s);
void update_table(char *s, int increment);
void remove_using_table(char *s);
int save_in_file(char* s, const char *file_name);
int table_at(const char c);
void print_table(void);
int compare(const void *a, const void *b);

#endif // STRM_H

#ifdef STRM_H_IMPLEMENTATION

void print_usage(void)
{
    printf("Usage: main <string>\n");
    printf("-v\t main -v <string>   \t\t\t remove vowels\n");
    printf("-d\t main -d <string>   \t\t\t remove duplicates\n");
    printf("-s\t main -s <string>   \t\t\t sort the output string\n");
    printf("-o\t main -o <file-name> <string>   \t save output string into file\n");
}

void transform(char *s, bool remove_vowels, bool remove_duplicates)
{
    remove_non_alpha(s);

    if (remove_vowels)
        update_table("aeiou\0", 2);
    if (remove_duplicates)
        update_table(s, 1);
    if (remove_vowels || remove_duplicates)
        remove_using_table(s);
}

void remove_non_alpha(char *s)
{
    size_t i = 0;
    size_t j = 0;
    while (s[i] != '\0') {
        if (isalpha(s[i])) {
            s[j++] = s[i];
        }
        i++;
    }
    s[j] = '\0';
}

void update_table(char *s, int increment)
{
    size_t i = 0;
    while (s[i] != '\0') {
        if (isupper(s[i])) {
            s[i] += 32;
        }

        table[s[i] - 97] += increment;
        i++;
    }
}

void remove_using_table(char *s)
{
    size_t i = 0;
    size_t j = 0;
    while (s[i] != '\0') {
        if (table_at(s[i]) < 2) {
            s[j++] = s[i];
        }
        i++;
    }
    s[j] = '\0';
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

void print_table(void)
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
