#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

// 1.1
// Is Unique: Implement an algorithm to determine if a string has all unique characters. What if you
// cannot use additional data structures?
// Assuming ASCII chars (1 byte )
#define NUM_ASCII_CHARS  (128)
#define ITEM_SIZE_BITS   (8*sizeof(uint32_t))
#define NUM_ITEMS        (NUM_ASCII_CHARS/ITEM_SIZE_BITS)

bool is_unique_ascii(char *str, int length) { // O(length)
  if (!str || !length) return false;
  uint32_t been_found[NUM_ITEMS] = {0};
  for (int i = 0, j = length-1;i < j; i++, j--) {
      if ( (been_found[str[i]/ITEM_SIZE_BITS] & (1 << (str[i] % ITEM_SIZE_BITS))) ||
           (been_found[str[j]/ITEM_SIZE_BITS] & (1 << (str[j] % ITEM_SIZE_BITS))) )
          return false;
      been_found[str[i]/ITEM_SIZE_BITS] |= (1 << (str[i] % ITEM_SIZE_BITS)); // O(1)
      been_found[str[j]/ITEM_SIZE_BITS] |= (1 << (str[j] % ITEM_SIZE_BITS)); // O(1)
  }
  return true;
}

bool is_unique_ascii_nocase(char *str, int length) { // O(length)
    if (!str || !length) return false;
    uint32_t been_found[NUM_ITEMS] = {0};
    for (int i = 0, j = length-1;i < j; i++, j--) {
        if ( (been_found[tolower(str[i])/ITEM_SIZE_BITS] & (1 << (tolower(str[i]) % ITEM_SIZE_BITS))) ||
             (been_found[tolower(str[j])/ITEM_SIZE_BITS] & (1 << (tolower(str[j]) % ITEM_SIZE_BITS))) )
            return false;
        been_found[tolower(str[i])/ITEM_SIZE_BITS] |= (1 << (tolower(str[i]) % ITEM_SIZE_BITS));
        been_found[tolower(str[j])/ITEM_SIZE_BITS] |= (1 << (tolower(str[j]) % ITEM_SIZE_BITS));
    }
    return true;
}

int main() {
    char *str = "Hello!";
    printf("is_unique_ascii(\"%s\")\t\t\t\t\t: %s\n", str, is_unique_ascii(str, strlen(str)) ? "true" : "false");
    printf("is_unique_ascii_nocase(\"%s\")\t\t\t: %s\n", str, is_unique_ascii_nocase(str, strlen(str)) ? "true" : "false");

    str = "World";
    printf("is_unique_ascii(\"%s\")\t\t\t\t\t: %s\n", str, is_unique_ascii(str, strlen(str)) ? "true" : "false");
    printf("is_unique_ascii_nocase(\"%s\")\t\t\t\t: %s\n", str, is_unique_ascii_nocase(str, strlen(str)) ? "true" : "false");

    str = "This cat";
    printf("is_unique_ascii(\"%s\")\t\t\t\t\t: %s\n", str, is_unique_ascii(str, strlen(str)) ? "true" : "false");
    printf("is_unique_ascii_nocase(\"%s\")\t\t\t: %s\n", str, is_unique_ascii_nocase(str, strlen(str)) ? "true" : "false");

    str = "bat";
    printf("is_unique_ascii(\"%s\")\t\t\t\t\t\t: %s\n", str, is_unique_ascii(str, strlen(str)) ? "true" : "false");
    printf("is_unique_ascii_nocase(\"%s\")\t\t\t\t: %s\n", str, is_unique_ascii_nocase(str, strlen(str)) ? "true" : "false");

    str = "abcdefg";
    printf("is_unique_ascii(\"%s\")\t\t\t\t\t: %s\n", str, is_unique_ascii(str, strlen(str)) ? "true" : "false");
    printf("is_unique_ascii_nocase(\"%s\")\t\t\t: %s\n", str, is_unique_ascii_nocase(str, strlen(str)) ? "true" : "false");

    str = "memories";
    printf("is_unique_ascii(\"%s\")\t\t\t\t\t: %s\n", str, is_unique_ascii(str, strlen(str)) ? "true" : "false");
    printf("is_unique_ascii_nocase(\"%s\")\t\t\t: %s\n", str, is_unique_ascii_nocase(str, strlen(str)) ? "true" : "false");

    str = "aAbBcCdDeEfFjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
    printf("is_unique_ascii(\"%s\")\t\t\t: %s\n", str, is_unique_ascii(str, strlen(str)) ? "true" : "false");
    printf("is_unique_ascii_nocase(\"%s\")\t: %s\n", str, is_unique_ascii_nocase(str, strlen(str)) ? "true" : "false");

    return 0;
}