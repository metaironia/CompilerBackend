#include <stdio.h>
#include <assert.h>

#include "../lib/oneginlib/functions_for_input.h"
#include "../lib/oneginlib/functions_for_output.h"

#include "../lib/tree/tree_func.h"
#include "../lib/tree/tree_log.h"

#include "../lib/tree/math_tree/dsl_commands.h"
#include "../lib/tree/math_tree/math_tree_func.h"

#include "ASTtoIR/ast_to_ir.h"

int main (const int argc, const char *argv[]) {

    IntRepr interm_repr = {};

    IntReprCtor (&interm_repr);
    IntReprDtor (&interm_repr);

    return 0;
}
