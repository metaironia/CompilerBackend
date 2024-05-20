#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#include "../ASTtoIR/ast_to_ir.h"
#include "../ASTtoIR/ir_dsl.h"

#include "ir_to_asm.h"

#define DEF_IR_CMD(interm_repr_cmd, asm_cmd)      {                                       \
                                                      case interm_repr_cmd:               \
                                                          fprintf (asm_file, "\t" asm_cmd);    \
                                                          break;                          \
                                                  }

#define DEF_IR_CMD_JMP(interm_repr_cmd, asm_cmd)  {                                                                                  \
                                                      case interm_repr_cmd:                                                          \
                                                          fprintf                  (asm_file, "\t" asm_cmd " ");                     \
                                                          IntReprCellAsmLabelPrint (asm_file, interm_repr_cell -> jump_cell_index);  \
                                                          fprintf                  (asm_file, "\n");                                 \
                                                          return IR_FUNC_STATUS_OK;                                                  \
                                                  }

#define DEF_IR_OP_REG(interm_repr_op, op_name)    {                                       \
                                                      case interm_repr_op:                \
                                                          fprintf (asm_file, op_name);    \
                                                          break;                          \
                                                  }

#define DEF_IR_OP(...)   

#define DEF_IR_CMD_COMM(...)

#define DEF_IR_CMD_FUNC(...)

const char *AsmFileNameGen (const char *output_file_name) {

    assert (output_file_name);

    static char output_asm_file_name[MAX_ASM_FILE_LENGTH] = {};

    snprintf (output_asm_file_name, MAX_ASM_FILE_LENGTH, "%s.asm", output_file_name);

    return output_asm_file_name;
}

IntReprFuncStatus IntReprToAsmFile (const IntRepr *interm_repr, const char *output_file_name) {

    assert (interm_repr);
    assert (output_file_name);

    FILE *asm_file = fopen (AsmFileNameGen (output_file_name), "w");

    IntReprAsmHeaderPrint (asm_file);

    IntReprAllCmdsToAsmPrint (asm_file, interm_repr);

    fprintf (asm_file, "\nsection .data\n\n");
    
    IntReprDoubleValDefPrint (asm_file, interm_repr);

    fprintf (asm_file, "\n%%include \"mystdlib/mystdlib.asm\"\n");

    fclose (asm_file);
    asm_file = NULL;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprAllCmdsToAsmPrint (FILE *asm_file, const IntRepr *interm_repr) {

    assert (asm_file);
    assert (interm_repr);

    for (size_t i = 0; i < (size_t) IR_SIZE_; i++) {

        if ((IR_CELL_ + i) -> is_jumpable_here) {

            IntReprCellAsmLabelPrint (asm_file, i);
            fprintf                  (asm_file, ":\n");
        }

        IntReprCmdToAsmPrint (asm_file, IR_CELL_ + i);
    }

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprDoubleValDefPrint (FILE *asm_file, const IntRepr *interm_repr) {

    assert (asm_file);
    assert (interm_repr);
        
    int label_num = 0;

    for (size_t i = 0; i < (size_t) IR_SIZE_; i++) {

        if (((IR_CELL_ + i) -> src_operand).operand_type       == IR_OP_IMMEDIATE &&
            ((IR_CELL_ + i) -> src_operand).operand_value_type == VALUE_TYPE_DOUBLE) {

            IntReprImmValAsmLabelPrint (asm_file, ((IR_CELL_ + i) -> src_operand).operand_value);

            fprintf (asm_file, "_%d: ", label_num++);

            fprintf (asm_file, "dq %.3lf\n", ((IR_CELL_ + i) -> src_operand).operand_value);
        }
    }

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprAsmHeaderPrint (FILE *asm_file) {

    assert (asm_file);

    fprintf (asm_file, "extern GetStdHandle  ; kernel32.dll\n"
                       "extern WriteConsoleA ; kernel32.dll\n"
                       "extern ReadConsoleA  ; kernel32.dll\n"
                       "extern ExitProcess   ; kernel32.dll\n"
                       "\n"
                       "section .text\n\n"
                       "_start:\n");

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprCmdToAsmPrint (FILE *asm_file, const IntReprCell *interm_repr_cell) {

    assert (interm_repr_cell);

    switch (interm_repr_cell -> cmd_type) {

        case IR_CMD_FUNC_START:
            fprintf (asm_file, "\n%s:\n", interm_repr_cell -> cmd_name);
            return IR_FUNC_STATUS_OK;

        case IR_CMD_FUNC_END:
            fprintf (asm_file, "\n");
            return IR_FUNC_STATUS_OK;

        case IR_CMD_FUNC_CALL:
            fprintf (asm_file, "\tcall %s\n", interm_repr_cell -> cmd_name);
            return IR_FUNC_STATUS_OK;

        case IR_CMD_COMMENT:
            fprintf (asm_file, "%s", interm_repr_cell -> cmd_name);
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
            IntReprImmValToAsmPrint (asm_file, interm_repr_operand);
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

IntReprFuncStatus IntReprImmValToAsmPrint (FILE *asm_file, const IntReprOperand *interm_repr_operand) {

    assert (asm_file);

    switch (interm_repr_operand -> operand_value_type) {

        case VALUE_TYPE_INT:
            fprintf (asm_file, "%" PRId64, (int64_t) (interm_repr_operand -> operand_value));
            break;

        case VALUE_TYPE_DOUBLE: {
            static int label_num = 0;
            fprintf (asm_file, "[rel ");
            IntReprImmValAsmLabelPrint (asm_file, interm_repr_operand -> operand_value);
            fprintf (asm_file, "_%d]", label_num++);
            break;
        }

        case NOT_A_VALUE:
            fprintf (stderr, "ATTEMPT TO PRINT NOT A VALUE TO ASM\n");
            return IR_FUNC_STATUS_FAIL;

        default:
            fprintf (stderr, "UNKNOWN VALUE TYPE TO PRINT TO ASM\n");
            return IR_FUNC_STATUS_FAIL;
    }

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprImmValAsmLabelPrint (FILE *asm_file, const double number) {

    assert (asm_file);

    fprintf (asm_file, "_DOUBLE__");

    if (number < 0)
        fprintf (asm_file, "neg_");

    const double abs_value = fabs (number);

    double int_part = 0;

    const double frac_part = modf (abs_value, &int_part);

    fprintf (asm_file, "%.0lf_%.0lf", int_part, frac_part);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprCellAsmLabelPrint (FILE *asm_file, const int64_t cell_to_jump) {

    assert (asm_file);

    fprintf (asm_file, ".L%" PRId64, cell_to_jump);

    return IR_FUNC_STATUS_OK;
}