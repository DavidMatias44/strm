#define STRM_H_IMPLEMENTATION
#include "strm.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage();
        exit(EXIT_FAILURE);
    }
    
    if (strcmp(argv[1], "--help") == 0) {
        print_usage();
        exit(EXIT_SUCCESS);
    }

    bool remove_vowels_flag     = false;
    bool remove_duplicates_flag = false;
    bool sort_result            = false;
    bool save_in_file_flag      = false;

    char *file_name = NULL;
    char file_extension[5] = ".txt\0";

    size_t index;
    for (index = 1; index < argc - 1; ++index) {
        if (argv[index][0] == '-') {
            switch (argv[index][1]) {
                case 'v': {
                    remove_vowels_flag = true;
                } break;
                case 'd': {
                    remove_duplicates_flag = true;
                } break;
                case 's': {
                    sort_result = true;
                } break;
                case 'o': {
                    if (++index >= argc - 1) {
                        fprintf(stderr, "Error: string or file name missing\n");
                        exit(EXIT_FAILURE);
                    }

                    file_name = (char *)malloc(sizeof(char)*strlen(argv[index]) + 5);
                    strcpy(file_name, argv[index]);
                    strcat(file_name, file_extension);
                    save_in_file_flag = true;
                } break;
                default: {
                    fprintf(stderr, "Error: flag not recognized\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    char *str = (char *)malloc(sizeof(char)*strlen(argv[index]) + 1);
    strcpy(str, argv[index]);
    transform(&str, remove_vowels_flag, remove_duplicates_flag);

    if (sort_result) {
        qsort(str, strlen(str), sizeof(char), compare);
    }

    if (save_in_file_flag) {
        printf("%s\n", file_name);
        if (save_in_file(str, file_name)) {
            fprintf(stderr, "Error saving string into file: %s\n", file_name);
            printf("%s\n", str);
        }
    } else {
        printf("%s\n", str);
    }

    return 0;
}

