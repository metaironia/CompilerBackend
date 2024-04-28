#ifndef BACKEND_H
#define BACKEND_H

#include <stdint.h>

#include "../../lib/tree/tree_func.h"
#include "../../lib/tree/tree_log.h"

#include "../../lib/tree/math_tree/dsl_commands.h"
#include "../../lib/tree/math_tree/math_tree_func.h"

#define CURRENT_FUNC_NAME_NODE(current_node)            current_node -> right_branch -> left_branch

#define CURRENT_FUNC_FIRST_END_LINE_NODE(current_node)  CURRENT_FUNC_NAME_NODE(current_node) -> right_branch


enum BackendFuncStatus {

    BACKEND_FUNC_STATUS_FAIL,
    BACKEND_FUNC_STATUS_OK
};

struct IntReprCell {

    const char  *cmd_name;
    int64_t      cmd_opcode;    
    IntReprCell *jump_ptr;
    int64_t      jump_addr;
    bool         is_patchable;
};

struct IntRepr {

    IntReprCell *cell;
    int64_t      size;
};

BackendFuncStatus TreeToIntRepr (FILE *asm_file, const Tree *lang_tree);

BackendFuncStatus IntReprCtor (IntRepr *interm_repr);

BackendFuncStatus IntReprDataCtor (IntRepr *interm_repr);

BackendFuncStatus IntReprDataDtor (IntRepr *interm_repr);

BackendFuncStatus IntReprDtor (IntRepr *interm_repr);

BackendFuncStatus IntReprBeginAndEnd (FILE *asm_file);

BackendFuncStatus IntReprInitFuncArgsWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprFuncNameWrite (FILE *asm_file, const TreeNode *current_func_node);

BackendFuncStatus IntReprNewFuncWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprLangOperatorWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprOperatorReadWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprOperatorPrintWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprOperatorIfWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprOperatorRetWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprOperatorWhileWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprOperatorOrAndWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprOperatorComparisonWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprConditionWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprOperatorAssignWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprMathExpressionWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprFuncCallWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprFuncPassedArgsWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprVarOrNumWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus IntReprMathOperatorWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus LangTreeVarsSet (Tree *lang_tree, const NameTable *lang_name_table);

BackendFuncStatus LangFuncVarsSet (TreeNode *current_node, const NameTable *lang_name_table,
                                   NameTable *local_func_name_table);

#endif
