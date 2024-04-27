#include <stdio.h>
#include <assert.h>

#include "../../lib/oneginlib/functions_for_input.h"
#include "../../lib/oneginlib/functions_for_output.h"

#include "../../lib/tree/tree_func.h"
#include "../../lib/tree/tree_log.h"

#include "../../lib/tree/math_tree/dsl_commands.h"
#include "../../lib/tree/math_tree/math_tree_func.h"

#include "backend.h"
#include "backend_input.h"

int main (const int argc, const char *argv[]) {

    if (BackendCmdArgsCheck (argc) == BACKEND_FUNC_STATUS_FAIL)
        return -1;

    NameTable lang_name_table = {};
    NameTableCtor (&lang_name_table);

    FILE *input_file = fopen (InputFileName (argv), "r");
    assert (input_file);

    Tree lang_tree = {};
    TreeCtor (&lang_tree);

    LangTreeNodeRead (input_file, &(lang_tree.root), &lang_name_table);
    assert (lang_tree.root);

    fclose (input_file);
    input_file = NULL;

    LangTreeVarsSet (&lang_tree, &lang_name_table);

    FILE *output_file = fopen (OutputFileName (argv), "w");
    assert (output_file);

    TreeToAsmFile (output_file, &lang_tree);

    fclose (output_file);
    output_file = NULL;

    NameTableDtor (&lang_name_table);
    TreeDtor (&lang_tree);

    return 0;
}
