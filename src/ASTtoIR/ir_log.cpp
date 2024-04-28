#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "ast_to_ir.h"
#include "ir_log.h"

static FILE *IR_LOG_FILE = IntReprLogFileCreate ("IR_log.txt");

FILE *IntReprLogFileCreate (const char *log_file_name) {

    assert (log_file_name);

    FILE *log_file = fopen (log_file_name, "w");
    assert (log_file);

    atexit (IntReprLogFileClose);

    return log_file;
}

void IntReprLogFileClose (void) {

    if (IR_LOG_FILE)
        fclose (IR_LOG_FILE);

    IR_LOG_FILE = NULL;
}

IntReprFuncStatus IntReprDump (const IntRepr *interm_repr) {

    assert (interm_repr);

    for (size_t i = 0; i < (size_t) (IR_SIZE_); i++) {

        IR_LOG_PRINT_ ("cell #%zu", i);

        IntReprCellDump (IR_CELL_ + i);
    }

    IR_LOG_PRINT_ ("\n");

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprCellDump (const IntReprCell *interm_repr_cell) {

    assert (interm_repr_cell);

    IR_LOG_PRINT_ ("    command name:                    %s\n",          interm_repr_cell -> cmd_name);
    IR_LOG_PRINT_ ("    command opcode:                  %" PRIx64 "\n", interm_repr_cell -> cmd_opcode);
    IR_LOG_PRINT_ ("    jump ptr to IntReprCell:         %p\n",          interm_repr_cell -> jump_ptr);
    IR_LOG_PRINT_ ("    jump addr in x86-64 (RIP-based): %" PRIx64 "\n", interm_repr_cell -> jump_addr);
    
    IR_LOG_PRINT_ ("    need to patch:                   ");

    if (interm_repr_cell -> need_patch)
        IR_LOG_PRINT_ ("YES\n")
    
    else
        IR_LOG_PRINT_ ("NO\n");

    return IR_FUNC_STATUS_OK;
}