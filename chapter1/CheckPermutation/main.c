#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <ctype.h>

#define NO (false)
#define YES (true)

#define DEBUG
// 1.2
// Check Permutation: Given two strings, write a method to decide if one is a permutation of the other.
// Assumption:
// 1. Space is significant
// 2. Case is significant
// 3. ASCII chars set
// 4. strings are null terminated

bool check_permutation(char *s, char *t, bool check_case) { // O(s+t)
    bool result = true;
    if (!s || !t || !*s || !*t || strlen(s) != strlen(t)) result = false;

#ifdef DEBUG
    printf("%s (\"%s\", \"%s\") : ", __func__, s, t);
#endif

    if (result) { // this is so that I can print

        int *s_set = (int *)calloc (128, sizeof(int));
        assert(s_set);

        for (size_t i = 0;(s[i]); i++) { // O(s)
            check_case ? s_set[s[i]]++ : s_set[tolower(s[i])]++;
        }
        for (size_t i = 0;(t[i]); i++) { // O(t)
            int count = check_case ? --s_set[t[i]] : --s_set[tolower(t[i])];
            if (count < 0) {
                result = false;
                break;
            }
        }
        free(s_set);
    }

#ifdef DEBUG
    printf("%s\n", result ? "true" : "false");
#endif
    return result;
}

int main() {
    check_permutation("ab", "", NO);
    check_permutation("", "", NO);
    check_permutation("Hello, World!", "world, Hello!", YES);
    check_permutation("Hello, World!", "world, Hello!", NO);
    check_permutation("abcdcba", "abcdcac", NO);
    check_permutation("a", "a", NO);
    check_permutation("ab", "ba", NO);
    check_permutation("ola    ", " la o", NO);
    return 0;
}
