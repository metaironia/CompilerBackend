#ifndef IR_TO_ASM_H
#define IR_TO_ASM_H

#include <stdio.h>

#include "../ASTtoIR/ast_to_ir.h"


const int MAX_ASM_FILE_LENGTH = 64;


const char *AsmFileNameGen (const char *output_file_name);

IntReprFuncStatus IntReprToAsmFile (const IntRepr *interm_repr, const char *output_file_name);

IntReprFuncStatus IntReprCmdToAsmFile (FILE *asm_file, const IntReprCell *interm_repr_cell);

IntReprFuncStatus IntReprDestOperandToAsmFile (FILE *asm_file, const IntReprCell *interm_repr_cell);

IntReprFuncStatus IntReprSrcOperandToAsmFile (FILE *asm_file, const IntReprCell *interm_repr_cell);

#endif