#ifndef BACKEND_H
#define BACKEND_H

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

BackendFuncStatus TreeToAsmFile (FILE *asm_file, const Tree *lang_tree);

BackendFuncStatus AsmFileBeginAndEnd (FILE *asm_file);

BackendFuncStatus AsmFileInitFuncArgsWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileFuncNameWrite (FILE *asm_file, const TreeNode *current_func_node);

BackendFuncStatus AsmFileNewFuncWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileLangOperatorWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileOperatorReadWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileOperatorPrintWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileOperatorIfWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileOperatorRetWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileOperatorWhileWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileOperatorOrAndWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileOperatorComparisonWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileConditionWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileOperatorAssignWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileMathExpressionWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileFuncCallWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileFuncPassedArgsWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileVarOrNumWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus AsmFileMathOperatorWrite (FILE *asm_file, const TreeNode *current_node);

BackendFuncStatus LangTreeVarsSet (Tree *lang_tree, const NameTable *lang_name_table);

BackendFuncStatus LangFuncVarsSet (TreeNode *current_node, const NameTable *lang_name_table,
                                   NameTable *local_func_name_table);

#endif
