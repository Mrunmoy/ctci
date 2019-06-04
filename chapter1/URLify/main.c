#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

//#define DEBUG

// 1.3
// URLify: Write a method to replace all spaces in a string with '%20': You may assume that the string
// has sufficient space at the end to hold the additional characters, and that you are given the "true"
// length of the string. (Note: If implementing in Java, please use a character array so that you can
// perform this operation in place.)
// EXAMPLE
// Input: "Mr John Smith ", 13
// Output: "Mr%20John%20Smith"


// Assumption:
// 0. leading spaces will also get converted to %20
// 1. null terminated string
// 2. truelength = length of string without counting trailing spaces or null char
//    For example: "this is      " -> 7 (4 + 1 + 2)
// 3. this function will remove all trailing spaces (wont get converted)
//

void urlify(char * const s, const size_t truelength) {
    if (!s || !*s || !truelength) return; // NULL pointer or empty string or 0 length

#ifdef DEBUG
    printf("%s (\"%s\", %lu): ", __func__, s, truelength);
#endif
    long space_count = 0;
    for (long i = 0; i < truelength; i++) {
        if (s[i] == ' ') space_count++;
    }
    // truelength already includes count of included space,
    // we need two more per count, hence x 2
    size_t new_length = truelength + space_count*2;
    s[new_length] = '\0'; // terminate new string
    size_t overwrite_idx = new_length - 1;
    for (long i = truelength - 1; i >= 0; i--) {
        if (s[i] == ' ') {
            s[overwrite_idx--] = '0';
            s[overwrite_idx--] = '2';
            s[overwrite_idx--] = '%';
        }
        else
            s[overwrite_idx--] = s[i];
    }
#ifdef DEBUG
    printf("%s [%3lu]\n", s, new_length);
#endif
}

int main(int argc, char  *argv[]) {
    if (argc > 1) {
        FILE *in_file = fopen(argv[1], "r");

        if (!in_file) {
            fprintf(stderr, "Error opening input file %s\n", argv[1]);
            exit(1);
        }

        char *str = (char *)calloc(200, sizeof(char));
        assert(str);
        while (fscanf(in_file, "%200[^\n]\n", str) != EOF) {
            // remove trailing spaces to get truelength
            size_t i = strlen(str) - 1;
            while (str[i] == ' ') str[i--] = '\0';

            urlify(str, strlen(str));

            printf("Result : %s\n", str);

            memset(str, 0, 200);
        }

        free(str);
    }
    else {
        printf("\nUsage: ./URLify filename\n[Limitation: Each line can contain upto 200 character input (including spaces)]\n");
    }
    return 0;
}