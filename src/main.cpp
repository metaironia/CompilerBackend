#include <stdio.h>
#include <assert.h>

#include "../lib/oneginlib/functions_for_input.h"
#include "../lib/oneginlib/functions_for_output.h"

#include "../lib/tree/tree_func.h"
#include "../lib/tree/tree_log.h"

#include "../lib/tree/math_tree/dsl_commands.h"
#include "../lib/tree/math_tree/math_tree_func.h"

#include "backend_input.h"

#include "ASTtoIR/ast_to_ir.h"
#include "ASTtoIR/ir_log.h"

int main (const int argc, const char *argv[]) {

    if (BackendCmdArgsCheck (argc) == BACKEND_FUNC_STATUS_FAIL)
        return -1;

    FILE *input_file = fopen (InputFileName (argv), "r");

    Tree lang_tree = {};
    TreeCtor (&lang_tree);

    NameTable lang_name_table = {};
    NameTableCtor (&lang_name_table);

    LangTreeNodeRead (input_file, &(lang_tree.root), &lang_name_table);
    assert (lang_tree.root);

    MathTreeGraphDump (&lang_tree, &lang_name_table);

    fclose (input_file);
    input_file = NULL;

    LangTreeVarsSet (&lang_tree, &lang_name_table);

    IntRepr interm_repr = {};
    IntReprCtor (&interm_repr);

int mem_disp = 0; //TODO put to another file

    IntReprLangOperatorWrite (&interm_repr, lang_tree.root, &mem_disp);    
    IntReprDump (&interm_repr);

    TreeDtor      (&lang_tree);
    NameTableDtor (&lang_name_table);
    IntReprDtor   (&interm_repr);

    return 0;
}
