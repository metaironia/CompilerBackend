#ifndef IR_TO_ASM_H
#define IR_TO_ASM_H

#include <stdio.h>

#include "../ASTtoIR/ast_to_ir.h"

const int MAX_ASM_FILE_LENGTH = 64;

const char *AsmFileNameGen (const char *output_file_name);

IntReprFuncStatus IntReprToAsmFile (const IntRepr *interm_repr, const char *output_file_name);

IntReprFuncStatus IntReprCmdToAsmPrint (FILE *asm_file, const IntReprCell *interm_repr_cell);

IntReprFuncStatus IntReprOperandToAsmPrint (FILE *asm_file, const IntReprOperand *interm_repr_operand);

IntReprFuncStatus IntReprOperandDispToAsmPrint (FILE *asm_file, const IntReprOperand *interm_repr_operand);

IntReprFuncStatus IntReprOperandTypeToAsmPrint (FILE *asm_file, const IntReprOperand *interm_repr_operand);

IntReprFuncStatus IntReprImmValAsmLabelPrint (FILE *asm_file, const double number);

#endif