#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "functions_for_input.h"
#include "strings_sort.h"

int StringForwardComparator (const void *a, const void *b) {

    const PtrToStr *first_string_struct  = (const PtrToStr *) a;
    const PtrToStr *second_string_struct = (const PtrToStr *) b;

    return MyStrcmpForward((first_string_struct  -> pointer_to_string),
                           (first_string_struct  -> string_length),
                           (second_string_struct -> pointer_to_string),
                           (second_string_struct -> string_length));
}

int StringBackwardComparator (const void *a, const void *b) {

    const PtrToStr *first_string_struct  = (const PtrToStr *) a;
    const PtrToStr *second_string_struct = (const PtrToStr *) b;

    return MyStrcmpBackward((first_string_struct  -> pointer_to_string),
                            (first_string_struct  -> string_length),
                            (second_string_struct -> pointer_to_string),
                            (second_string_struct -> string_length));
}

int MyStrcmpForward (const char *const first_string,  int64_t first_str_length,
                     const char *const second_string, int64_t second_str_length) {

    int64_t first_str_index  = 0;
    int64_t second_str_index = 0;

    while (first_str_index <= first_str_length &&
           ((char) (tolower(*(first_string + first_str_index))) > 'z' ||
            (char) (tolower(*(first_string + first_str_index))) < 'a')) {

        first_str_index++;
    }

    while (second_str_index <= second_str_length &&
           ((char) (tolower(*(second_string + second_str_index))) > 'z' ||
            (char) (tolower(*(second_string + second_str_index))) < 'a')) {

        second_str_index++;
    }

    while (first_str_index <= first_str_length && second_str_index <= second_str_length) {

        if ((char) (tolower(*(first_string + first_str_index))) <
            (char) (tolower(*(second_string + second_str_index)))) {

            return -1;
        }

        if ((char) (tolower(*(first_string + first_str_index))) >
            (char) (tolower(*(second_string + second_str_index)))) {

            return 1;
        }

        first_str_index++;
        second_str_index++;
    }

    return (first_str_length >= second_str_length ? -1 : 1);
}


int MyStrcmpBackward (const char *const first_string,  int64_t first_str_length,
                      const char *const second_string, int64_t second_str_length) {

    int64_t first_str_index  = first_str_length;
    int64_t second_str_index = second_str_length;

    while (first_str_index >= 0 &&
           ((char) (tolower(*(first_string + first_str_index))) > 'z' ||               //TODO isletter
            (char) (tolower(*(first_string + first_str_index))) < 'a')) {

        first_str_index--;
    }

    while (second_str_index >= 0 &&
           ((char) (tolower(*(second_string + second_str_index))) > 'z' ||
            (char) (tolower(*(second_string + second_str_index))) < 'a')) {           //TODO make var to letters

        second_str_index--;
    }

    while (first_str_index >= 0 && second_str_index >= 0) {

        if ((char) (tolower(*(first_string + first_str_index))) <
            (char) (tolower(*(second_string + second_str_index)))) {

            return -1;
        }

        if ((char) (tolower(*(first_string + first_str_index))) >
            (char) (tolower(*(second_string + second_str_index)))) {

            return 1;
        }

        first_str_index--;
        second_str_index--;
    }

    return (first_str_length >= second_str_length ? -1 : 1);
}

void StringsSort (void *const ptrs_to_strings, const int64_t num_of_str,
                          int64_t elem_size, int (*comp) (const void *a, const void *b)) {

    qsort (ptrs_to_strings, num_of_str, elem_size, comp);
}

/*
void BubbleSort (void *const ptrs_to_strings, const int64_t num_of_elements,
                 int64_t elem_size, int (*comp) (const void *a, const void *b)) {

    array_for_sort =

    for (int64_t counter = 0; counter < num_of_elements; counter++) {

        for (int64_t index = 0; index < num_of_elements - counter; index++) {

            if (comp ())
        }
    }
}
*/
