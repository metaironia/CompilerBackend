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

enum IntReprFuncStatus {

    IR_FUNC_STATUS_OK,
    IR_FUNC_STATUS_FAIL
};

enum OperandType {

    IR_OP_IMMEDIATE,
    IR_OP_REG_RAX,
    IR_OP_REG_RBX,
    IR_OP_REG_RCX,
    IR_OP_REG_RDX,
    IR_OP_REG_R10,
    IR_OP_REG_R11,
    IR_OP_REG_R12,
    IR_OP_REG_R13,
    IR_OP_REG_R14,
    IR_OP_REG_RBP,
    IR_OP_REG_RSP,
    IR_OP_REG_XMM0,
    IR_OP_REG_XMM1,
    IR_OP_REG_XMM2,
    IR_OP_REG_XMM3,
    IR_OP_REG_XMM4
};

enum CommandType {

    IR_CMD_ADD,
    IR_CMD_SUB,
    IR_CMD_MUL,
    IR_CMD_DIV,
    IR_CMD_PUSH,
    IR_CMD_POP,
    IR_CMD_MOV
};

struct IntReprCell {

    const char  *cmd_name;
    CommandType  cmd_type;

    OperandType  dest_operand_type;  
    double       dest_operand_value;
    int64_t      dest_operand_disp;
    bool         is_dest_operand_mem;

    OperandType  src_operand_type;
    double       src_operand_value;
    int64_t      src_operand_disp;
    bool         is_src_operand_mem;

    IntReprCell *jump_ptr;
    int64_t      jump_addr;
    bool         need_patch;
};

struct IntRepr {

    IntReprCell *cell;
    int64_t      size;
    int64_t      capacity;
};

IntReprFuncStatus TreeToIntRepr (FILE *asm_file, const Tree *lang_tree);

IntReprFuncStatus IntReprCtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDataCtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDataDtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDataRecalloc (IntRepr *interm_repr);

IntReprFuncStatus IntReprEmit (IntRepr *interm_repr, 
                               const char        *cmd_name,          const CommandType cmd_type,
                               const OperandType  dest_operand_type, const double      dest_operand_value,
                               const int64_t      dest_operand_disp, const bool        is_dest_operand_mem,
                               const OperandType  src_operand_type,  const double      src_operand_value,
                               const int64_t      src_operand_disp,  const bool        is_src_operand_mem,
                                     IntReprCell *jump_ptr,          const int64_t     jump_addr,
                               const bool         need_patch);

IntReprFuncStatus IntReprBeginAndEnd (FILE *asm_file);

IntReprFuncStatus IntReprInitFuncArgsWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprFuncNameWrite (FILE *asm_file, const TreeNode *current_func_node);

IntReprFuncStatus IntReprNewFuncWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprLangOperatorWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprOperatorReadWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprOperatorPrintWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprOperatorIfWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprOperatorRetWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprOperatorWhileWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprOperatorOrAndWrite (IntRepr *interm_repr, const TreeNode *current_node);

IntReprFuncStatus IntReprOperatorComparisonWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprConditionWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprOperatorAssignWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprMathExpressionWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprFuncCallWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprFuncPassedArgsWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprVarOrNumWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus IntReprMathOperatorWrite (IntRepr *interm_repr, const TreeNode *current_node, int *mem_disp);

IntReprFuncStatus LangTreeVarsSet (Tree *lang_tree, const NameTable *lang_name_table);

IntReprFuncStatus LangFuncVarsSet (TreeNode *current_node, const NameTable *lang_name_table,
                                   NameTable *local_func_name_table);

#endif
