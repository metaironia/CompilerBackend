#include <assert.h>
#include <math.h>
#include <sys\stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "functions_for_input.h"

char *BufFromFile (const char *file_name, struct stat *file_stat) {

    FILE *ptr_to_file = fopen (file_name, "rb");
    assert (ptr_to_file);

    stat (file_name, file_stat);

    char *buf = BufferMaker (file_stat -> st_size);

    FileToBuf (ptr_to_file, buf, file_stat -> st_size);

    fclose (ptr_to_file);
    ptr_to_file = NULL;

    return buf;
}

char *BufferMaker (const off_t buf_size) {

    char *buffer = (char *) calloc (buf_size + 1, sizeof (char));

    if (buffer == NULL) {

        fprintf (stderr, "Not enough memory. Program was finished.");
        return 0;
    }

    return buffer;
}

PtrToStr *PointersToStringsMaker (const int64_t number_of_strings) {

    PtrToStr *ptr_to_strings = (PtrToStr *) calloc (number_of_strings, sizeof (PtrToStr));

    if (ptr_to_strings == NULL) {

        fprintf (stderr, "Not enough memory. Program was finished. You will go to the HELL.");
        return 0;
    }

    return ptr_to_strings;
}

void FileToBuf (FILE *const text, char *const buffer, const off_t buf_size) {

    assert (buffer);
    assert (text);

    if (fread (buffer, sizeof (char), (int64_t) buf_size, text) != ((int64_t) buf_size))
        assert (!"DEBIL! Use \"rb\" in fopen() when open the file with \"Onegin\" poem please.");

    //TODO fix type conversion bug

    buffer[buf_size] = '\0';

    char *n_symbol = NULL;

    while ((n_symbol = strrchr (buffer, '\n')) != NULL)
        *n_symbol = '\0';
}

int64_t StringCounter (const char *const buffer, const off_t buf_size) {

    assert (buffer);

    int64_t num_of_str = 0;

    for (int64_t counter = 0; counter < (int64_t) buf_size + 1; counter++)
        if (buffer[counter] == '\0')
            num_of_str++;

    return num_of_str;
}

void SetPointersToBuf (PtrToStr *const ptrs_to_strings, char *const buffer, off_t buf_size,
                       int64_t num_of_str) {

    assert (buffer);
    assert (ptrs_to_strings);

    int64_t current_num_of_str = 0;
    char *buf_ptr_index = buffer;

    while (current_num_of_str < num_of_str && (buffer + buf_size) - buf_ptr_index >= 0) {

        (ptrs_to_strings[current_num_of_str].pointer_to_string) = buf_ptr_index;
        (ptrs_to_strings[current_num_of_str].string_length)     = strlen (buf_ptr_index);

        buf_ptr_index = (char *) strchr (buf_ptr_index, '\0') + 1;
        current_num_of_str++;
    }
}

void SlashRSymbolChecker (PtrToStr *const ptrs_to_strings, const int64_t num_of_str) {

    assert (ptrs_to_strings);

    char *r_symbol_exist = NULL;

    for (int64_t current_num_of_str = 0; current_num_of_str < num_of_str; current_num_of_str++) {

        if ((r_symbol_exist = strchr (ptrs_to_strings[current_num_of_str].pointer_to_string, '\r'))) {

            *r_symbol_exist = '\0';
            (ptrs_to_strings[current_num_of_str].string_length) -= 1;
        }
    }
}

const char *InputFileName (const char *argvv[]) {

    return argvv[1];
}

