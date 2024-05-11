#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "ast_to_ir.h"
#include "ir_log.h"
#include "ir_dsl.h"

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

    IR_LOG_PRINT_ ("    command name:                       %s\n",            interm_repr_cell -> cmd_name);
    IR_LOG_PRINT_ ("    command type:                       %s\n",            CommandTypeNameGet (interm_repr_cell -> cmd_type));
    IR_LOG_PRINT_ ("    destination operand:                %s\n",            OperandTypeNameGet (interm_repr_cell -> dest_operand_type));
    IR_LOG_PRINT_ ("    destination operand value:          %lg\n",           interm_repr_cell -> dest_operand_value);
    IR_LOG_PRINT_ ("    destination operand displacement:   0x%" PRIx64 "\n", interm_repr_cell -> dest_operand_disp);

    IR_LOG_PRINT_ ("    is dest operand has mem type:       ");
    
    IntReprFieldStatePrint (interm_repr_cell -> is_dest_operand_mem);
        
    IR_LOG_PRINT_ ("    source operand:                     %s\n",            OperandTypeNameGet (interm_repr_cell -> src_operand_type));
    IR_LOG_PRINT_ ("    source operand value:               %lg\n",           interm_repr_cell -> src_operand_value);
    IR_LOG_PRINT_ ("    source operand displacement:        0x%" PRIx64 "\n", interm_repr_cell -> src_operand_disp);

    IR_LOG_PRINT_ ("    is source operand has mem type:     ");

    IntReprFieldStatePrint (interm_repr_cell -> is_src_operand_mem);

    IR_LOG_PRINT_ ("    jump ptr to IntReprCell:            %p\n",            interm_repr_cell -> jump_ptr);
    IR_LOG_PRINT_ ("    jump addr in byte code (RIP-based): 0x%" PRIx64 "\n", interm_repr_cell -> jump_addr);
    
    IR_LOG_PRINT_ ("    need patch:                         ");

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

const char *OperandTypeNameGet (const OperandType operand_type) {

    switch (operand_type) {

        RETURN_ENUM_NAME (IR_OP_IMMEDIATE);
        RETURN_ENUM_NAME (IR_OP_REG_RAX);
        RETURN_ENUM_NAME (IR_OP_REG_RBX);
        RETURN_ENUM_NAME (IR_OP_REG_RCX);
        RETURN_ENUM_NAME (IR_OP_REG_RDX);
        RETURN_ENUM_NAME (IR_OP_REG_R10);
        RETURN_ENUM_NAME (IR_OP_REG_R11);
        RETURN_ENUM_NAME (IR_OP_REG_R12);
        RETURN_ENUM_NAME (IR_OP_REG_R13);
        RETURN_ENUM_NAME (IR_OP_REG_R14);
        RETURN_ENUM_NAME (IR_OP_REG_RBP);
        RETURN_ENUM_NAME (IR_OP_REG_RSP);
        RETURN_ENUM_NAME (IR_OP_REG_XMM0);
        RETURN_ENUM_NAME (IR_OP_REG_XMM1);
        RETURN_ENUM_NAME (IR_OP_REG_XMM2);
        RETURN_ENUM_NAME (IR_OP_REG_XMM3);
        RETURN_ENUM_NAME (IR_OP_REG_XMM4);

        default:
            return "UNKNOWN OPERAND TYPE";
    }

    return "OPERAND TYPE GET NAME FUNCTION FAILED";
}

const char *CommandTypeNameGet (const CommandType command_type) {

    switch (command_type) {

        RETURN_ENUM_NAME (IR_CMD_ADD);
        RETURN_ENUM_NAME (IR_CMD_SUB);
        RETURN_ENUM_NAME (IR_CMD_MUL);
        RETURN_ENUM_NAME (IR_CMD_DIV);
        RETURN_ENUM_NAME (IR_CMD_PUSH);
        RETURN_ENUM_NAME (IR_CMD_POP);
        RETURN_ENUM_NAME (IR_CMD_MOV);

        default:
            return "UNKNOWN COMMAND TYPE";
    }

    return "COMMAND TYPE GET NAME FUNCTION FAILED";
}