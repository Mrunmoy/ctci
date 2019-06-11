/**
 *  @file stringbuilder.c
 *  @author championsurfer3044
 *  @date 11 Jun 2019 
 *  @brief 
 *
 *  LICENSE:-
 *  The MIT License (MIT)
 *  Copyright (c) 2019 Mrunmoy Samal
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom
 *  the Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall
 *  be included in all copies or substantial portions of the
 *  Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 *  OR OTHER DEALINGS IN THE SOFTWARE.
 */


/*
*----------------------------------------------------------------------
*   Include Files
*----------------------------------------------------------------------
*/
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include "stringbuilder.h"

/*
*----------------------------------------------------------------------
*   Private Defines
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Macros
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Data Types
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Public Variables
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Variables (static)
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Public Constants (const)
*----------------------------------------------------------------------
*/


/*
*----------------------------------------------------------------------
*   Private Constants (static)
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Function Prototypes (static)
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Externs
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Functions Definitions
*----------------------------------------------------------------------
*/

static void expand_if_necessary(string_builder_t *sb_obj, size_t required_size) {
    if (!sb_obj) return;

    size_t length_needed = 0;
    if (sb_obj->c_string) {
        length_needed = strlen(sb_obj->c_string) + required_size /* new character */ + 1 /* null terminator */;
        if (sb_obj->size <= length_needed) {
            while (sb_obj->size <= length_needed) sb_obj->size *= 2;
            sb_obj->c_string = realloc(sb_obj->c_string, sb_obj->size*sizeof(char));
            assert(sb_obj->c_string);
        }
    } else {
        length_needed = required_size + 1 /* null terminator */;
        sb_obj->c_string = calloc(length_needed, sizeof(char));
        assert(sb_obj->c_string);
        sb_obj->size = length_needed;
    }
    sb_obj->c_string[length_needed-1] = '\0';
    length_needed;
}

static void append_char(string_builder_t *sb_obj, char ch) {
    if (!sb_obj) return;

    expand_if_necessary(sb_obj, 1); // O (logN)

    size_t char_count = strlen(sb_obj->c_string);
    sb_obj->c_string[char_count++] = ch;
    sb_obj->c_string[char_count] = '\0';
}


static void append_int(string_builder_t *sb_obj, int val) {
    if (!sb_obj) return;

    size_t char_count = 0;
    while (val) {
        if (val < 10) {
            char_count++;
            break;
        }
        char_count++;
        val /= 10;
    }

    expand_if_necessary(sb_obj, char_count);

    char_count = strlen(sb_obj->c_string);
    while (val) {
        if (val < 10) {
            sb_obj->c_string[char_count++] = (char)('0' + val % 10);
            break;
        }
        sb_obj->c_string[char_count++] = (char)('0' + val/10);
        val /= 10;
    }
    sb_obj->c_string[char_count] = '\0';
}


/*
*----------------------------------------------------------------------
*   Exported Functions Definitions
*----------------------------------------------------------------------
*/
string_builder_t *new_string_builder(void)
{
    string_builder_t *obj = malloc (sizeof(string_builder_t));
    obj->c_string    = NULL;
    obj->size      = 0;
    obj->append_char = append_char;
    obj->append_int  = append_int;
}

void destroy_string_builder(string_builder_t *sb_obj) {
    if (sb_obj) {
        if (sb_obj->c_string) free(sb_obj->c_string);
        free(sb_obj);
    }
}