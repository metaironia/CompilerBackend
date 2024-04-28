#ifndef FUNCTIONS_FOR_OUTPUT_H
#define FUNCTIONS_FOR_OUTPUT_H

#include <stdint.h>

#include "functions_for_input.h"

void PrintOriginal (FILE *const output_file, const char *const buffer, const off_t buf_size);

void PrintAll (FILE *const output_file, PtrToStr *const ptrs_to_strings, const int64_t num_of_str);

void inline PrintLine (FILE *const output_file);

const char *OutputFileName (const char *argvv[]);

#endif
