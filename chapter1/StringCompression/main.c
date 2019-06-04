#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

// 1.6
// String Compression: Implement a method to perform basic string compression using the counts
// of repeated characters. For example, the string aabcccccaaa would become
// a2b1c5a3.
//
// If the "compressed" string would not become smaller than the original
// string, your method should return the original string.
//
// You can assume the string has only uppercase and lowercase letters (a - z).

static int count_digits(int value) {
    int count = 0;
    while (value) {
        count++;
        value /= 10;
    }
    return count;
}

static void copy_original(char *src, char *dest, size_t size) {
    strncpy(dest, src, size);
}

static int append_char_and_freq(char *str, int available, char  ch, int freq) {

    if (available < count_digits(freq)) {
        return -1;
    }
    int index = 0;
    str[index++] = ch; // append char first
    // append count
    while (freq) {
        if (freq < 10) {
            str[index++] = '0' + freq % 10;
            break;
        }
        str[index++] = '0' + freq/10;
        freq /= 10;
    }
    return index;
}

char *compress_string(char *str) {
    if (!str) return NULL; // NULL
    if (!str[0]) return calloc(1, 1); // return empty string

    size_t orig_length = strlen(str);

    char *out_str = malloc(orig_length); // todo: check if safe to allocate
    if (orig_length <= 2) {
        goto error;
    }

    int jump;
    int count = 1;
    char ch = str[0];
    size_t j = 0;
    for (size_t i = 1; i < orig_length; i++) {
        if (ch == str[i])
            count++;
        else {
            jump = append_char_and_freq(&out_str[j], orig_length - j, ch, count);
            if (jump < 0)
                goto error;
            j += jump;
            count = 1;
            ch = str[i];
        }
    }
    // handle the last char sequence
    jump = append_char_and_freq(&out_str[j], orig_length - j, ch, count);
    if (jump < 0)
        goto error;
    j += jump;
    if (j > orig_length)
        goto error;
    out_str[j] = '\0';
    return out_str;

error:
    copy_original(str, out_str, orig_length);
    out_str[orig_length] = '\0';
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

