#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 1.5
// One Away: There are three types of edits that can be performed on strings: insert a character,
// remove a character, or replace a character. Given two strings, write a function to check if they are
// one edit (or zero edits) away.
// EXAMPLE
// pale, pIe -> true
// pales. pale -> true
// pale. bale -> true
// pale. bake -> false

static bool check_one_char_replace(char *first, char *second) {
    bool detected = false;
    for (size_t i = 0;i < strlen(first); i++) {
        if (!detected)
            detected = (first[i] != second[i]);
        else if (first[i]!= second[i])
            return false;
    }
    return true;
}

static bool check_one_char_insert(char *small, char *large) {
    size_t sml_idx = 0;
    size_t lrg_idx = 0;
    while ( sml_idx < strlen(small) && lrg_idx < strlen(large) ) {\
    if (small[sml_idx] != large[lrg_idx]) {
            if (sml_idx != lrg_idx) return false; // only one mismatch allowed
            // found a place for insertion in small string,
            // skip this char in large string
            lrg_idx++;
            continue;
        }
        sml_idx++;
        lrg_idx++;
    }
    return true;
}

static bool one_edit_away(char *str1, char *str2) {
    if (!str1 && !str2) return false; // null strings
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    printf("%s ( %-30s, %-30s ) : ", __func__, str1, str2);
    bool result = false;
    if (len1 == len2)
        result = check_one_char_replace(str1, str2);
    else if (len1 == len2 + 1)
        result = check_one_char_insert(str2, str1);
    else if (len2 == len1 + 1)
        result = check_one_char_insert(str1, str2);
    printf("%s\n", result? "true" : "false");
    return result;
}


int main() {
    one_edit_away("", "");
    one_edit_away("", "a");
    one_edit_away("a", "");
    one_edit_away("", "ab");
    one_edit_away("ab", "a");
    one_edit_away("b", "ab");
    one_edit_away("Hello!", "ello!");
    one_edit_away("Hello!", "Hello");
    one_edit_away("pale", "ple");
    one_edit_away("pales", "pale");
    one_edit_away("pale", "bale");
    one_edit_away("pale", "bake");
    return 0;
}
