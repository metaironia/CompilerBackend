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
    IR_LOG_PRINT_ ("    destination operand:             %d\n",          interm_repr_cell -> dest_operand);
    IR_LOG_PRINT_ ("    source operand:                  %d\n",          interm_repr_cell -> src_operand);
    IR_LOG_PRINT_ ("    destination operand offset:      %" PRIx64 "\n", interm_repr_cell -> dest_operand_offset);
    IR_LOG_PRINT_ ("    source operand offset:           %" PRIx64 "\n", interm_repr_cell -> src_operand_offset);
    
    IR_LOG_PRINT_ ("    is dest operand has mem type:    ");

    IntReprFieldStatePrint (interm_repr_cell -> is_dest_operand_mem);
        
    IR_LOG_PRINT_ ("    is source operand has mem type:  ");

    IntReprFieldStatePrint (interm_repr_cell -> is_src_operand_mem);

    IR_LOG_PRINT_ ("    jump ptr to IntReprCell:         %p\n",          interm_repr_cell -> jump_ptr);
    IR_LOG_PRINT_ ("    jump addr in x86-64 (RIP-based): %" PRIx64 "\n", interm_repr_cell -> jump_addr);
    
    IR_LOG_PRINT_ ("    need patch:                      ");

    IntReprFieldStatePrint (interm_repr_cell -> need_patch);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprFieldStatePrint (bool field_status) {

    if (field_status)
        IR_LOG_PRINT_ ("YES\n")
    
    else
        IR_LOG_PRINT_ ("NO\n");

    return IR_FUNC_STATUS_OK;   
}