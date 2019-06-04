#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

// 1.4
// Palindrome Permutation: Given a string, write a function to check if it is a permutation of a palindrome.
// A palindrome is a word or phrase that is the same forwards and backwards. A permutation
// is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words.
// EXAMPLE
// Input: Tact Coa
// Output: True (permutations: "taco cat". "atco cta". etc.)

// Assumption:
// 1. standard ascii set alphabets (26 chars)
// 2. case insignificant
// 3. ignore space character

bool isPermutationOfPalindrome(char *str) {
    if (!str || !*str) return false;

    // Special case
    if (strlen(str) == 1) return true;

    uint32_t charmap = 0;
    for (long i = 0; i < strlen(str); i++) {
        if ( (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') )
            charmap ^=  (uint32_t)(1 << (tolower(str[i]))); // toggle bit
    }

    return (0 == charmap) || (0 == (charmap & (charmap-1)));
}



int main() {
    char *strlist[] = {
            "a",
            "ab",
            "A nut for a jar of tuna",
            "World",
            "Al lets Della call Ed \"Stella\"",
            "Halo World",
            "Amore, Roma",
            "Are we not pure? \"No, sir!\" Panama's moody Noriega brags. \"It is garbage!\" Irony dooms a man—a prisoner up to new era",
            "Borrow or rob",
            "King, are you glad you are king?",
            "Taco cat",
            "Was it a car or a cat I saw?"
    };

    for(int i = 0; i < sizeof(strlist)/sizeof(strlist[0]); i++) {
        printf("isPermutationOfPalindrome (%-117s) | %s\n", strlist[i], isPermutationOfPalindrome(strlist[i]) ? "true" : "false");
    }

    return 0;
}