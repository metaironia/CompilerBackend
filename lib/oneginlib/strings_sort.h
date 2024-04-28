#ifndef STRINGS_SORT_H
#define STRINGS_SORT_H

#include <stdint.h>

#include "functions_for_output.h"

int StringForwardComparator (const void *a, const void *b);

int StringBackwardComparator (const void *a, const void *b);

void StringsSort (void *const ptrs_to_strings, const int64_t num_of_str,
                          int64_t elem_size, int (*comp) (const void *a, const void *b));

int MyStrcmpForward (const char *const first_string,  int64_t first_str_length,
                     const char *const second_string, int64_t second_str_length);

int MyStrcmpBackward (const char *const first_string,  int64_t first_str_length,
                      const char *const second_string, int64_t second_str_length);

#endif
