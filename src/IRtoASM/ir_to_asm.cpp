#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#include "../ASTtoIR/ast_to_ir.h"
#include "../ASTtoIR/ir_dsl.h"

#include "ir_to_asm.h"

#define DEF_IR_CMD(interm_repr_cmd, asm_cmd)    {                                       \
                                                    case interm_repr_cmd:               \
                                                        fprintf (asm_file, asm_cmd);    \
                                                        break;                          \
                                                }

#define DEF_IR_OP_REG(interm_repr_op, op_name)  {                                       \
                                                    case interm_repr_op:                \
                                                        fprintf (asm_file, op_name);    \
                                                        break;                          \
                                                }

#define DEF_IR_OP(...)   

#define DEF_IR_CMD_FUNC(...)

const char *AsmFileNameGen (const char *output_file_name) {

    assert (output_file_name);

    static char output_asm_file_name[MAX_ASM_FILE_LENGTH] = {};

    snprintf (output_asm_file_name, MAX_ASM_FILE_LENGTH, "asm_%s", output_file_name);

    return output_asm_file_name;
}

IntReprFuncStatus IntReprToAsmFile (const IntRepr *interm_repr, const char *output_file_name) {

    assert (interm_repr);
    assert (output_file_name);

    FILE *asm_file = fopen (AsmFileNameGen (output_file_name), "w");

    fprintf (asm_file, ".text\n");

    for (size_t i = 0; i < (size_t) IR_SIZE_; i++)
        IntReprCmdToAsmPrint (asm_file, IR_CELL_ + i);

    fclose (asm_file);
    asm_file = NULL;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprCmdToAsmPrint (FILE *asm_file, const IntReprCell *interm_repr_cell) {

    assert (interm_repr_cell);

    if (interm_repr_cell -> cmd_type == IR_CMD_FUNC_START) {        // IR_CMD_FUNC_START is one specific case

        fprintf (asm_file, "%s:\n", interm_repr_cell -> cmd_name);
        return IR_FUNC_STATUS_OK;
    }

    switch (interm_repr_cell -> cmd_type) {

        case IR_CMD_FUNC_START:
            fprintf (asm_file, "%s:\n", interm_repr_cell -> cmd_name);
            return IR_FUNC_STATUS_OK;

        case IR_CMD_FUNC_END:
            fprintf (asm_file, "\n");
            return IR_FUNC_STATUS_OK;

        #include "../ir_commands.h"

        default:
            fprintf (stderr, "UNKNOWN CMD TYPE TO PRINT TO ASM\n");
            return IR_FUNC_STATUS_FAIL;
    }

    fprintf (asm_file, " ");

    IntReprOperandToAsmPrint (asm_file, &(interm_repr_cell -> dest_operand));

    if ((interm_repr_cell -> dest_operand).operand_type != IR_OP_NO_OPERAND &&
        (interm_repr_cell -> src_operand).operand_type  != IR_OP_NO_OPERAND)

        fprintf (asm_file, ", ");

    IntReprOperandToAsmPrint (asm_file, &(interm_repr_cell -> src_operand));

    fprintf (asm_file, "\n");

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprOperandToAsmPrint (FILE *asm_file, const IntReprOperand *interm_repr_operand) {

    assert (asm_file);
    assert (interm_repr_operand);

    const bool is_operand_mem = interm_repr_operand -> is_operand_mem;

    if (is_operand_mem)
        fprintf (asm_file, "[");

    IntReprOperandDispToAsmPrint (asm_file, interm_repr_operand);

    if (is_operand_mem)
        fprintf (asm_file, "]");

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprOperandDispToAsmPrint (FILE *asm_file, const IntReprOperand *interm_repr_operand) {

    assert (asm_file);
    assert (interm_repr_operand);

    IntReprOperandTypeToAsmPrint (asm_file, interm_repr_operand);

    int64_t operand_disp = interm_repr_operand -> operand_disp; 

    if (operand_disp != IR_POISON)
        fprintf (asm_file, "%+" PRId64, operand_disp);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprOperandTypeToAsmPrint (FILE *asm_file, const IntReprOperand *interm_repr_operand) {

    assert (asm_file);
    assert (interm_repr_operand);

    switch (interm_repr_operand -> operand_type) {

        case IR_OP_IMMEDIATE:
            fprintf (asm_file, "_DOUBLE_%.3lf", interm_repr_operand -> operand_value);
            break; 

        case IR_OP_NO_OPERAND:
            break;

        #include "../ir_operands.h"       

        default:
            fprintf (stderr, "UNKNOWN OPERAND TYPE TO PRINT TO ASM\n");
            return IR_FUNC_STATUS_FAIL;
    }

    return IR_FUNC_STATUS_OK;
}
/*
uint64_t DoubleToHexCast (const double double_to_cast) {

    const char *one_byte = (char *) &double_to_cast;
    
    uint64_t cast_double = 0;

    for (size_t i = 0; i < sizeof (double); i++) {

        
    }

}
*/
IntReprFuncStatus IntReprImmValAsmLabelPrint (FILE *asm_file, const double number) {

    fprintf (asm_file, "_DOUBLE_");

    if (number < 0)
        fprintf (asm_file, "neg_");

    fprintf (asm_file, "%lf", number);

    return IR_FUNC_STATUS_OK;
}
