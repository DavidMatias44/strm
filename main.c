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
            }
        }
    }

    char *str = (char *)malloc(sizeof(char)*strlen(argv[index]) + 1);
    strcpy(str, argv[index]);
    transform(&str, remove_vowels_flag, remove_duplicates_flag);

    if (sort_result) {
        qsort(str, strlen(str), sizeof(char), compare);
    }

    printf("%s\n", str);

    return 0;
}

