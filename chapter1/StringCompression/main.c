#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include "stringbuilder.h"

// 1.6
// String Compression: Implement a method to perform basic string compression using the counts
// of repeated characters. For example, the string aabcccccaaa would become
// a2b1c5a3.
//
// If the "compressed" string would not become smaller than the original
// string, your method should return the original string.
//
// You can assume the string has only uppercase and lowercase letters (a - z).

char *compress_string(char *str) {
    if (!str) return NULL; // NULL
    if (!str[0]) return calloc(1, 1); // return empty string

    string_builder_t  *sb_obj = NULL;
    size_t orig_length = strlen(str);

    char *out_str = malloc(orig_length); // todo: check if safe to allocate

    if (orig_length <= 2) {
        goto error;
    }

    sb_obj = new_string_builder();

    int count = 0;

    for (size_t i = 0; i < orig_length; i++) { // O(orig_length)
        count++;
        if ( i + 1 > orig_length || str[i] != str[i+1]) {
            sb_obj->append_char(sb_obj, str[i]); // O(1)
            sb_obj->append_int(sb_obj, count); // O(#digits)
            count = 0;
        }
    }

    if (strlen(sb_obj->c_string) < orig_length)
        strncpy(out_str, sb_obj->c_string, orig_length);
    else
error:
        strncpy(out_str, str, orig_length);
    out_str[orig_length] = '\0';

    destroy_string_builder(sb_obj);
    return out_str;
}



static void runner(char *str) {
    printf("Original String: %s\n", str);

    char * result = compress_string(str);

    printf("After Compression: %s\n\n", result);

    free(result);
}

int main() {
    runner("a");
    runner("aa");
    runner("aabcccccaaa");
    runner("saabccqcraaaac");
    return 0;
}

