#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "ast_to_ir.h"
#include "ir_log.h"
#include "ir_dsl.h"

#define DEF_IR_OP_REG            DEF_IR_OP

#define DEF_IR_OP(ir_op, ...)    RETURN_ENUM_NAME (ir_op);

#define DEF_IR_CMD_COMM          DEF_IR_CMD

#define DEF_IR_CMD_FUNC          DEF_IR_CMD

#define DEF_IR_CMD_JMP           DEF_IR_CMD

#define DEF_IR_CMD(ir_cmd, ...)  RETURN_ENUM_NAME (ir_cmd);

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

    IR_LOG_PRINT_ ("IR capacity = %" PRId64 "\n", IR_CAPACITY_);
    IR_LOG_PRINT_ ("IR size     = %" PRId64 "\n", IR_SIZE_);

    for (size_t i = 0; i < (size_t) (IR_SIZE_); i++) {

        IR_LOG_PRINT_ ("cell #%zu\n", i);

        IntReprCellDump (IR_CELL_ + i);
    }

    IR_LOG_PRINT_ ("\n");

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprCellDump (const IntReprCell *interm_repr_cell) {

    assert (interm_repr_cell);

    IR_LOG_PRINT_             ("    command name:                       %s\n",  interm_repr_cell -> cmd_name);
    IR_LOG_PRINT_             ("    command type:                       %s\n",  CommandTypeNameGet (interm_repr_cell -> cmd_type));
    IR_LOG_PRINT_             ("    destination operand:                %s\n",  OperandTypeNameGet ((interm_repr_cell -> dest_operand).operand_type));
    IR_LOG_PRINT_             ("    destination operand value type:     %s\n",  ValueTypeNameGet   ((interm_repr_cell -> dest_operand).operand_value_type));
    IR_LOG_PRINT_             ("    destination operand value:          %lg\n", (interm_repr_cell -> dest_operand).operand_value);
    IR_LOG_PRINT_             ("    destination operand displacement:   ");
    
    IntReprIsFieldPoisonPrint ((interm_repr_cell -> dest_operand).operand_disp);

    IR_LOG_PRINT_             ("    is dest operand has mem type:       ");
    
    IntReprFieldStatePrint    ((interm_repr_cell -> dest_operand).is_operand_mem);

    IR_LOG_PRINT_             ("    source operand:                     %s\n",  OperandTypeNameGet ((interm_repr_cell -> src_operand).operand_type));
    IR_LOG_PRINT_             ("    source operand value type:          %s\n",  ValueTypeNameGet   ((interm_repr_cell -> src_operand).operand_value_type));
    IR_LOG_PRINT_             ("    source operand value:               %lg\n", (interm_repr_cell -> src_operand).operand_value);
    IR_LOG_PRINT_             ("    source operand displacement:        ");

    IntReprIsFieldPoisonPrint ((interm_repr_cell -> src_operand).operand_disp);

    IR_LOG_PRINT_             ("    is source operand has mem type:     ");

    IntReprFieldStatePrint    ((interm_repr_cell -> src_operand).is_operand_mem);

    IR_LOG_PRINT_             ("    jump ptr to IntReprCell:            0x%p\n", interm_repr_cell -> jump_ptr);
    IR_LOG_PRINT_             ("    jump index in IntRepr:              ");
    
    IntReprIsFieldPoisonPrint (interm_repr_cell -> jump_cell_index);

    IR_LOG_PRINT_             ("    jump addr in byte code (RIP-based): 0x%" PRIx64 "\n", interm_repr_cell -> jump_addr);
    
    IR_LOG_PRINT_             ("    is jumpable here:                   ");

    IntReprFieldStatePrint    (interm_repr_cell -> is_jumpable_here);
    
    IR_LOG_PRINT_             ("    need patch:                         ");

    IntReprFieldStatePrint (interm_repr_cell -> need_patch);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprFieldStatePrint (const bool field_status) {

    if (field_status)
        IR_LOG_PRINT_ ("YES\n")
    
    else
        IR_LOG_PRINT_ ("NO\n");

    return IR_FUNC_STATUS_OK;   
}

IntReprFuncStatus IntReprIsFieldPoisonPrint (const int64_t field_value) {

    if (field_value == IR_POISON)
        IR_LOG_PRINT_ ("POISON\n")
    
    else
        IR_LOG_PRINT_ ("%" PRId64 "\n", field_value);

    return IR_FUNC_STATUS_OK;
}

const char *OperandTypeNameGet (const OperandType operand_type) {

    switch (operand_type) {

        #include "../ir_operands.h"

        default:
            return "UNKNOWN OPERAND TYPE";
    }

    return "OPERAND TYPE GET NAME FUNCTION FAILED";
}

const char *CommandTypeNameGet (const CommandType command_type) {

    switch (command_type) {

        #include "../ir_commands.h"

        default:
            return "UNKNOWN COMMAND TYPE";
    }

    return "COMMAND TYPE GET NAME FUNCTION FAILED";
}

const char *ValueTypeNameGet (const ValueType value_type) {

    switch (value_type) {

        case VALUE_TYPE_DOUBLE:
            return "VALUE_TYPE_DOUBLE";

        case VALUE_TYPE_INT:
            return "VALUE_TYPE_INT";

        case NOT_A_VALUE:
            return "NOT_A_VALUE";

        default:
            return "UNKNOWN VALUE TYPE";
    }

    return "VALUE TYPE GET NAME FUNCTION FAILED";
}