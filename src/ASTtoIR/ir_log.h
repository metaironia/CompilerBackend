#ifndef IR_LOG_H
#define IR_LOG_H

#include <stdio.h>

#include "ast_to_ir.h"

#define IR_LOG_PRINT_(...)      {                                       \
                                    fprintf (IR_LOG_FILE, __VA_ARGS__); \
                                    fflush (IR_LOG_FILE);               \
                                }

#define RETURN_ENUM_NAME(enum)  case enum:        \
                                    return #enum;

FILE *IntReprLogFileCreate (const char *log_file_name);

void IntReprLogFileClose (void);

IntReprFuncStatus IntReprDump (const IntRepr *interm_repr);

IntReprFuncStatus IntReprCellDump (const IntReprCell *interm_repr_cell);

IntReprFuncStatus IntReprFieldStatePrint (const bool field_status);

IntReprFuncStatus IntReprIsFieldPoisonPrint (const int64_t field_value);

const char *OperandTypeNameGet (const OperandType operand_type);

const char *CommandTypeNameGet (const CommandType command_type);

const char *ValueTypeNameGet (const ValueType value_type);

#endif