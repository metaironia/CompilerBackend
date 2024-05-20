#ifndef BACKEND_H
#define BACKEND_H

#include <stdint.h>

#include "../../lib/tree/tree_func.h"
#include "../../lib/tree/tree_log.h"

#include "../../lib/tree/math_tree/dsl_commands.h"
#include "../../lib/tree/math_tree/math_tree_func.h"

#define CURRENT_FUNC_NAME_NODE(current_node)            current_node -> right_branch -> left_branch

#define CURRENT_FUNC_FIRST_END_LINE_NODE(current_node)  CURRENT_FUNC_NAME_NODE(current_node) -> right_branch

const int IR_DEFAULT_CAPACITY = 1;

const int IR_INCREASE_NUM = 2;

const int STACK_CELL_SIZE = 8;

const int FUNC_MAX_ARGUMENTS_AMOUNT = 32;

const int64_t IR_POISON = 0xFEE1DEAD; 

enum IntReprFuncStatus {

    IR_FUNC_STATUS_OK,
    IR_FUNC_STATUS_FAIL
};

enum OperandType {

    #define  DEF_IR_OP_REG          DEF_IR_OP
    #define  DEF_IR_OP(ir_op, ...)  ir_op,
    #include "../ir_operands.h"
    #undef   DEF_IR_OP
    #undef   DEF_IR_OP_REG
};

enum CommandType {

    #define  DEF_IR_CMD_COMM          DEF_IR_CMD
    #define  DEF_IR_CMD_JMP           DEF_IR_CMD
    #define  DEF_IR_CMD_FUNC          DEF_IR_CMD
    #define  DEF_IR_CMD(ir_cmd, ...)  ir_cmd,
    #include "../ir_commands.h"
    #undef   DEF_IR_CMD
    #undef   DEF_IR_CMD_FUNC
    #undef   DEF_IR_CMD_COMM
    #undef   DEF_IR_CMD_JMP
};

enum ValueType {

    VALUE_TYPE_INT,
    VALUE_TYPE_DOUBLE,
    NOT_A_VALUE
};

struct IntReprOperand {

    OperandType  operand_type;  
    double       operand_value; //TODO fix truncated int
    ValueType    operand_value_type;
    int64_t      operand_disp;
    bool         is_operand_mem;
};

struct IntReprCell {

    const char  *cmd_name;
    CommandType  cmd_type;

    IntReprOperand dest_operand;
    IntReprOperand src_operand;

    IntReprCell *jump_ptr;
    int64_t      jump_cell_index;
    int64_t      jump_addr;
    bool         is_jumpable_here;
    bool         need_patch;
};

struct IntRepr {

    IntReprCell *cell;
    int64_t      size;
    int64_t      capacity;
};

IntReprFuncStatus IntReprCtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDataCtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDataDtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDataRecalloc (IntRepr *interm_repr);

IntReprFuncStatus IntReprEmit (IntRepr *interm_repr, 
                               const char        *cmd_name,            const CommandType cmd_type,
                               const OperandType  dest_operand_type,   const ValueType   dest_value_type,
                               const double       dest_operand_value,  const int64_t     dest_operand_disp,
                               const bool         is_dest_operand_mem, const OperandType src_operand_type, 
                               const ValueType    src_value_type,      const double      src_operand_value,
                               const int64_t      src_operand_disp,    const bool        is_src_operand_mem,
                                     IntReprCell *jump_ptr,            const int64_t     jump_cell_index,
                               const int64_t      jump_addr,           const bool        need_patch);

IntReprFuncStatus TreeToIntRepr (IntRepr *interm_repr, const Tree *lang_tree);

IntReprFuncStatus IntReprBeginAndEnd (IntRepr *interm_repr);

IntReprFuncStatus IntReprInitFuncArgsWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprFuncNameWrite (IntRepr *interm_repr, const TreeNode *current_func_node);

IntReprFuncStatus IntReprFuncPrologueWrite (IntRepr *interm_repr);

IntReprFuncStatus IntReprFuncEpilogueWrite (IntRepr *interm_repr);

IntReprFuncStatus IntReprNewFuncWrite (IntRepr *interm_repr, const TreeNode *current_node);

IntReprFuncStatus IntReprLangOperatorWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprOperatorReadWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprOperatorPrintWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprOperatorIfWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprOperatorRetWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprOperatorWhileWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprOperatorOrAndWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprOperatorComparisonWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprConditionWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprOperatorAssignWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprMathExpressionWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprFuncCallWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprFuncPassedArgsWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprVarOrNumWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprMathOperatorWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus LangTreeVarsSet (Tree *lang_tree, const NameTable *lang_name_table);

IntReprFuncStatus LangFuncVarsSet (TreeNode *current_node, const NameTable *lang_name_table,
                                   NameTable *local_func_name_table);

#endif
