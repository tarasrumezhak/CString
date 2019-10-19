#include <stdio.h>
#include "example.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("\n");
        printf("here, have some guidance\n");
        printf("usage is: %s <filepath> <filepath>\n", argv[0]);
        printf("\n");

        return 0;
    }

    FILE* source = fopen(argv[1], "r");
    if (source == NULL) {
        fprintf(stderr, "sorry, can't open: %s\n", argv[1]);

        return 1;
    }

    FILE* dest = fopen(argv[2], "w");
    if (dest == NULL) {
        fprintf(stderr, "sorry, can't open: %s\n", argv[2]);

        return 1;
    }

    return sort_letters(source, dest);
}
