#ifndef BACKEND_H
#define BACKEND_H

#include <stdint.h>

#include "../../lib/tree/tree_func.h"
#include "../../lib/tree/tree_log.h"

#include "../../lib/tree/math_tree/dsl_commands.h"
#include "../../lib/tree/math_tree/math_tree_func.h"

#define IR_CELL_                                        (interm_repr -> cell)

#define IR_SIZE_                                        (interm_repr -> size)

#define CURRENT_FUNC_NAME_NODE(current_node)            current_node -> right_branch -> left_branch

#define CURRENT_FUNC_FIRST_END_LINE_NODE(current_node)  CURRENT_FUNC_NAME_NODE(current_node) -> right_branch


enum IntReprFuncStatus {

    IR_FUNC_STATUS_OK,
    IR_FUNC_STATUS_FAIL
};

struct IntReprCell {

    const char  *cmd_name;
    int64_t      cmd_opcode;    
    IntReprCell *jump_ptr;
    int64_t      jump_addr;
    bool         need_patch;
};

struct IntRepr {

    IntReprCell *cell;
    int64_t      size;
};

IntReprFuncStatus TreeToIntRepr (FILE *asm_file, const Tree *lang_tree);

IntReprFuncStatus IntReprCtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDataCtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDataDtor (IntRepr *interm_repr);

IntReprFuncStatus IntReprDtor (IntRepr *interm_repr);

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

IntReprFuncStatus IntReprOperatorOrAndWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprOperatorComparisonWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprConditionWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprOperatorAssignWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprMathExpressionWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprFuncCallWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprFuncPassedArgsWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprVarOrNumWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus IntReprMathOperatorWrite (FILE *asm_file, const TreeNode *current_node);

IntReprFuncStatus LangTreeVarsSet (Tree *lang_tree, const NameTable *lang_name_table);

IntReprFuncStatus LangFuncVarsSet (TreeNode *current_node, const NameTable *lang_name_table,
                                   NameTable *local_func_name_table);

#endif
