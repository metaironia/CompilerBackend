#ifndef FUNCTIONS_FOR_INPUT_H
#define FUNCTIONS_FOR_INPUT_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct PtrToStr {
    int64_t string_length;
    char *pointer_to_string;
};

char *BufFromFile (const char *file_name, struct stat *file_stat);

char *BufferMaker (const off_t buf_size);

PtrToStr *PointersToStringsMaker (const int64_t number_of_strings);

void FileToBuf (FILE *const text, char *const buffer, const off_t buf_size);

int64_t StringCounter (const char *const buffer, const off_t buf_size);

void SetPointersToBuf (PtrToStr *const ptrs_to_strings, char *const buffer, off_t buf_size,
                       int64_t num_of_str);

void SlashRSymbolChecker (PtrToStr *const ptrs_to_strings, const int64_t num_of_str);

const char *InputFileName (const char *argvv[]);


#endif
