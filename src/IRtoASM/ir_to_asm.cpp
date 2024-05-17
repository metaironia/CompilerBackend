#include <stdio.h>
#include <assert.h>

#include "../ASTtoIR/ast_to_ir.h"
#include "../ASTtoIR/ir_dsl.h"

#include "ir_to_asm.h"

#define DEF_IR_CMD(interm_repr_cmd, asm_cmd)    {                                       \
                                                    case interm_repr_cmd:               \
                                                        fprintf (asm_file, asm_cmd);    \
                                                        break;                          \
                                                }

const char *AsmFileNameGen (const char *output_file_name) {

    assert (output_file_name);

    static char output_asm_file_name[MAX_ASM_FILE_LENGTH] = {};

    snprintf (output_asm_file_name, MAX_ASM_FILE_LENGTH, "asm_%s", output_file_name);

    return output_asm_file_name;
}

IntReprFuncStatus IntReprToAsmFile (const IntRepr *interm_repr, const char *output_file_name) {

    assert (interm_repr);
    assert (output_file_name);

    FILE *asm_file = fopen (output_file_name, "w");

    for (size_t i = 0; i < IR_SIZE_; i++)
        IntReprCmdToAsmFile (asm_file, IR_CELL_ + i);

    fclose (asm_file);
    asm_file = NULL;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprCmdToAsmFile (FILE *asm_file, const IntReprCell *interm_repr_cell) {

    assert (interm_repr_cell);

    if (interm_repr_cell -> cmd_type == IR_CMD_FUNC_START) {        // IR_CMD_FUNC_START is one specific case

        fprintf (asm_file, "%s:\n", interm_repr_cell -> cmd_name);
        return IR_FUNC_STATUS_OK;
    }

    switch (interm_repr_cell -> cmd_type) {

        #include "../ir_commands.h"
    }

    fprintf (asm_file, " ");

    IntReprDestOperandToAsmFile (asm_file, interm_repr_cell);

    if (interm_repr_cell -> dest_operand_type != IR_OP_NO_OPERAND &&
        interm_repr_cell -> src_operand_type != IR_OP_NO_OPERAND)

        fprintf (asm_file, ", ");

    IntReprSrcOperandToAsmFile (asm_file, interm_repr_cell);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprDestOperandToAsmFile (FILE *asm_file, const IntReprCell *interm_repr_cell) {

    assert (asm_file);
    assert (interm_repr_cell);

    
}

IntReprFuncStatus IntReprSrcOperandToAsmFile (FILE *asm_file, const IntReprCell *interm_repr_cell) {

    assert (asm_file);
    assert (interm_repr_cell);
}

