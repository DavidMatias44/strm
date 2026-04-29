#define STRM_H_IMPLEMENTATION
#include "strm.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage();
        exit(EXIT_FAILURE);
    }

    bool remove_dups_flag   = false;
    bool save_in_file_flag  = false;
    bool sort_result_flag   = false;
    bool remove_vowels_flag = false;

    char *str = NULL;
    char *file_name = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "dho:sv")) != -1) {
        switch (opt) {
            case 'd':
                remove_dups_flag = true;
                break;
            case 'h':
                print_usage();
                exit(EXIT_FAILURE);
                break;
            case 'o':
                save_in_file_flag = true;
                file_name = optarg;
                break;
            case 's':
                sort_result_flag = true; 
                break;
            case 'v':
                remove_vowels_flag = true;
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        print_usage();
    }
   
    str = argv[optind];
    transform(&str, remove_vowels_flag, remove_dups_flag);

    if (sort_result_flag) {
        qsort(str, strlen(str), sizeof(char), compare);
    }

    if (save_in_file_flag) {
        printf("saving into: %s\n", file_name);
        if (save_in_file(str, file_name)) {
            fprintf(stderr, "Error saving string");
            printf("%s\n", str);
        }
    } else {
        printf("%s\n", str);
    }

    return 0;
}
