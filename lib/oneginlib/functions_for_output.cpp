#include <assert.h>
#include <math.h>
#include <stdint.h>

#include "functions_for_output.h"

void PrintOriginal (FILE *const output_file, const char *const buffer, const off_t buf_size) {

    assert (output_file);
    assert (buffer);

    for (const char *buf_ptr_index = buffer; (buffer + buf_size) - buf_ptr_index >= 0;
         buf_ptr_index = (char *) strchr (buf_ptr_index, '\0') + 1) {

        if (*buf_ptr_index) {

            fputs (buf_ptr_index, output_file);
            fputs ("\n", output_file);
        }
    }
}

void PrintAll (FILE *const output_file, PtrToStr *const ptrs_to_strings, const int64_t num_of_str) {

    assert (ptrs_to_strings);
    assert (output_file);

    for (int64_t current_num_of_str = 0; current_num_of_str < num_of_str; current_num_of_str++) {

        if ((ptrs_to_strings[current_num_of_str].string_length) != 0) {

            fputs ((ptrs_to_strings[current_num_of_str].pointer_to_string), output_file);
            fputs ("\n", output_file);
        }
    }
}

void PrintLine (FILE *const output_file) {

    fprintf (output_file,"\n"
                         "-----------------------------------------------------------------------------"
                         "\n");
}

const char *OutputFileName (const char *argvv[]) {

    return argvv[2];
}
