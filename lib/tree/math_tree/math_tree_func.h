#ifndef MATH_TREE_FUNC_H
#define MATH_TREE_FUNC_H

#include "math_tree_node_data.h"
#include "../tree_func.h"

//TODO put below to dsl_commands

#define IS_VALUE_EQUAL(val, branch)   (current_node -> branch -> data -> nodeType == NUMBER &&                             \
                                      IsDoublesEqual ((current_node -> branch -> data -> nodeValue).mathNodeValue, val))

#define NODE_VALUE                    ((current_node -> data -> nodeValue).mathNodeValue)

#define NODE_TYPE                     (current_node -> data -> nodeType)

#define NODE_MATH_OPERATOR            ((current_node -> data -> nodeValue).mathOperator)

#define NODE_LANG_OPERATOR            ((current_node -> data -> nodeValue).langOperator)

#define BRANCH_VALUE(branch)          ((current_node -> branch -> data -> nodeValue).mathNodeValue)

#define BRANCH_TYPE(branch)           ((current_node -> branch -> data -> nodeType))

#define BRANCH_OPERATOR(branch)       ((current_node -> branch -> data -> nodeValue).mathOperator)


#define MATH_TREE_VERIFY(math_tree, func_type, name_table)                              \
                                {                                                       \
                                    if (MathTreeVerify (math_tree, __func__) != 0) {    \
                                                                                        \
                                        MathTreeGraphDump (math_tree, name_table);      \
                                                                                        \
                                        return func_type##_FUNC_STATUS_FAIL;            \
                                    }                                                   \
                                }

#define MATH_TREE_VERIFY_PTR_FUNC(math_tree)                                            \
                                {                                                       \
                                    if (MathTreeVerify (math_tree, __func__) != 0) {    \
                                                                                        \
                                        MathTreeGraphDump (math_tree);                  \
                                                                                        \
                                        return NULL;                                    \
                                    }                                                   \
                                }

#define MATH_TREE_NODE_VERIFY(math_tree_node, func_type)                            \
                                {                                                   \
                                    if (MathTreeNodeVerify (math_tree_node) != 0)   \
                                        return func_type##_FUNC_STATUS_FAIL;        \
                                }

#define MATH_TREE_NODE_VERIFY_PTR_FUNC(math_tree_node)                                  \
                                {                                                       \
                                    if (MathTreeNodeVerify (math_tree_node) != 0)       \
                                        return NULL;                                    \
                                }

#define NAME_TABLE_SET_AND_PRINT_ERROR(current_error)                                   \
                                {                                                       \
                                    LOG_PRINT (TREE_LOG_FILE, #current_error);          \
                                    LOG_PRINT (TREE_LOG_FILE, " has occured.\n");       \
                                    errors_name_table |= current_error;                 \
                                }

#define NAME_TABLE_VERIFY(name_table, func_type)                                        \
                                {                                                       \
                                    if (NameTableVerify (name_table, __func__) != 0)    \
                                        return func_type##_FUNC_STATUS_FAIL;            \
                                }


#define MATH_TREE_VERIFY_UNSIGNED_FUNC(math_tree, name_table)                           \
                                {                                                       \
                                    if (MathTreeVerify (math_tree, __func__) != 0) {    \
                                                                                        \
                                        MathTreeGraphDump (math_tree, name_table);      \
                                                                                        \
                                        return DEAD_TREE;                               \
                                    }                                                   \
                                }

#define MATH_TREE_NODE_VERIFY_UNSIGNED_FUNC(math_tree_node)                         \
                                {                                                   \
                                    if (MathTreeNodeVerify (math_tree_node) != 0)   \
                                        return DEAD_TREE_NODE;                      \
                                }

#define NAME_TABLE_VERIFY_UNSIGNED_FUNC(name_table)                                     \
                                {                                                       \
                                    if (NameTableVerify (name_table, __func__) != 0)    \
                                        return DEAD_NAME_TABLE;                         \
                                }

const int MAX_NUMBER_LENGTH = 30;

enum NameTableDef {

    NAME_TABLE_KEYWORD,
    NAME_TABLE_VARIABLE
};

struct NameTableCell {

    NameTableDef word_type;
    size_t word_number;
    char *word_name;
};

struct NameTable {

    NameTableCell *name_table_cell;
    size_t table_size;
    size_t table_capacity;
};

enum NameTableErrors {

    NAME_TABLE_NULL_PTR = (1 << 0),
    NAME_TABLE_CELL_NULL_PTR = (1 << 1),
    // NAME_TABLE_MULTIPLE_VARS_ONE_NAME = (1 << 2)
};

const int DEFAULT_NAME_TABLE_SIZE = 4;
const int NAME_TABLE_INCREASE_NUM = 2;

const int DEAD_TREE       = 0xDEAD1;
const int DEAD_TREE_NODE  = 0xDEAD2;
const int DEAD_NAME_TABLE = 0xDEAD3;

MathNodeType IsOperatorUnaryOrBinary (const MathNodeOperator node_operator_to_check);

TreeNode *CreateMathTreeNode (const MathNodeType type_of_node, const double node_value,
                              TreeNode *const ptr_left_branch,
                              TreeNode *const ptr_right_branch);

TreeNode *CreateLangTreeNode (const LangNodeOperator node_operator, TreeNode *const ptr_left_branch,
                              TreeNode *const ptr_right_branch);

unsigned int MathTreeNodeVerify (const TreeNode *math_expression_tree_node);

unsigned int MathTreeVerify (const Tree *math_expression_tree,
                             const char* name_parent_func);

unsigned int MathTreeNodeChecker (const TreeNode *math_expression_node);

unsigned int MathNodeTypeCheckError (const TreeNode *math_expression_node);

unsigned int NodeBinaryOperatorCheckErrors (const TreeNode *math_expression_node);

unsigned int NodeUnaryOperatorCheckErrors (const TreeNode *math_expression_node);

unsigned int NodeVariableCheckErrors (const TreeNode *math_expression_node);

unsigned int NodeNumberCheckErrors (const TreeNode *math_expression_node);

const char *NumberToString (const double number);

const char *MathNodeTypeToString (const TreeNode *math_tree_node, const NameTable *name_table);

const char *LangNodeTypeToString (const TreeNode *current_node);

const char *LangNodeOperatorToString (const LangNodeOperator current_operator);

const char *MathNodeNumVarEndToString (const TreeNode *math_tree_node, const NameTable *name_table);

const char *MathNodeOperatorToString (const TreeNode *math_tree_node);

TreeFuncStatus MathTreeNodeConstantsSimplify (TreeNode *math_expression_node);

TreeFuncStatus MathTreeNodeBinaryOperatorSimplify (TreeNode *math_expression_node);

TreeFuncStatus MathTreeNodeNumAndNumSimplify (TreeNode *node_for_simplify);

TreeFuncStatus MathTreeNodeSmthAndZeroSimplify (TreeNode *node_for_simplify);

TreeFuncStatus MathTreeNodeSmthAndOneSimplify (TreeNode *node_for_simplify);

double MathTreeCompute (const Tree *math_expression_tree, const double variable_value);

double MathTreeNodeCompute (const TreeNode *math_tree_node, const double variable_value);

double MathTreeNodeComputeOperatorResult (const TreeNode *math_tree_node,
                                          const double left_branch_node_value,
                                          const double right_branch_node_value,
                                          const double variable_value);

double MathTreeNodeUnaryCompute (const double left_branch_value,
                                 const MathNodeOperator current_node_operator);

double MathTreeNodeBinaryCompute (const double left_branch_value, const double right_branch_value,
                                  const MathNodeOperator current_node_operator);

TreeFuncStatus NameTableCtor (NameTable *name_table);

TreeFuncStatus NameTableAdd (NameTable *name_table, const NameTableDef word_type,
                                                    const char *word_name,
                                                    const size_t word_number);

TreeFuncStatus NameTableRecalloc (NameTable *name_table);

long long NameTableWordFind (const NameTable *name_table, const char *word_name,
                             const long long start_index);

const char *NameTableRepeatCheck (const NameTable *name_table);

unsigned int NameTableVerify (const NameTable *name_table, const char *parent_func_name);

TreeFuncStatus NameTableDtor (NameTable *name_table);

const char *NameTableVariableFind (const size_t variable_index, const NameTable *name_table);

TreeFuncStatus LangTreeNodeRead (FILE *file_for_read_tree, TreeNode **tree_node_for_fill,
                                 NameTable *name_table);

TreeFuncStatus TreeNodeNilCheck (FILE *file_for_node_nil_check);

TreeFuncStatus LangTreeNodeDataRead (FILE *file_for_read_node_data, TreeNode **tree_node_for_data_read,
                                     NameTable *name_table);

bool CheckIfWordIsNumber (char *word_to_check, TreeNode **current_node);

bool CheckIfWordIsVariable (const char *word_to_check, TreeNode **current_node, NameTable *name_table);

TreeFuncStatus LangTreeFilePrint (FILE *output_file, const Tree *lang_tree, const NameTable *name_table);

TreeFuncStatus LangTreeNodeFilePrint (FILE *output_file, const TreeNode *lang_tree_node,
                                      const NameTable *name_table);

#endif
