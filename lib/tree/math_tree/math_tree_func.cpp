#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dsl_commands.h"

#include "../tree_func.h"
#include "../tree_log.h"

#include "math_tree_func.h"
#include "math_tree_node_data.h"

#include "math_operation.h"

extern FILE *TREE_LOG_FILE;

TreeNode *CreateMathTreeNode (const MathNodeType type_of_node, const double node_value,
                              TreeNode *const ptr_left_branch,
                              TreeNode *const ptr_right_branch) {

    TreeNode *current_node = CreateTreeNode ();
    assert (current_node);

    current_node -> data = (MathNode *) calloc (1, sizeof (MathNode));
    assert (current_node -> data);

    if ((type_of_node != NUMBER && type_of_node != VARIABLE && type_of_node != END) &&
        IsOperatorUnaryOrBinary ((MathNodeOperator) node_value) != type_of_node)

        return NULL;

    current_node -> data -> nodeType = type_of_node;

    if (type_of_node == NUMBER || type_of_node == VARIABLE)
        NODE_VALUE = node_value;

    else
        NODE_MATH_OPERATOR = (MathNodeOperator) node_value;

    current_node -> left_branch  = ptr_left_branch;
    current_node -> right_branch = ptr_right_branch;

    return current_node;
}

TreeNode *CreateLangTreeNode (const LangNodeOperator node_operator, TreeNode *const ptr_left_branch,
                              TreeNode *const ptr_right_branch) {

    TreeNode *current_node = CreateTreeNode ();
    assert (current_node);

    current_node -> data = (MathNode *) calloc (1, sizeof (MathNode));
    assert (current_node -> data);

    current_node -> data -> nodeType = LANGUAGE_OPERATOR;

    NODE_LANG_OPERATOR = node_operator;

    current_node -> left_branch  = ptr_left_branch;
    current_node -> right_branch = ptr_right_branch;

    return current_node;
}

MathNodeType IsOperatorUnaryOrBinary (const MathNodeOperator node_operator_to_check) {

    switch (node_operator_to_check) {

        case OPERATOR_ADD:
        case OPERATOR_SUB:
        case OPERATOR_DIV:
        case OPERATOR_MUL:
        case OPERATOR_POW:
        case OPERATOR_EQUAL:
        case OPERATOR_NOT_EQUAL:
        case OPERATOR_GREATER:
        case OPERATOR_GREATER_EQ:
        case OPERATOR_LESS_EQ:
        case OPERATOR_LESS:
            return BINARY_OPERATOR;
            break;

        case OPERATOR_SIN:
        case OPERATOR_COS:
        case OPERATOR_LN:
        case OPERATOR_SQRT:
        case OPERATOR_OPEN_PARENTHESIS:
        case OPERATOR_CLOSE_PARENTHESIS:
            return UNARY_OPERATOR;
            break;

        default:
            return NODE_TYPE_ERROR;
    }

    return NODE_TYPE_ERROR;
}

const char *LangNodeTypeToString (const TreeNode *current_node) {

    MATH_TREE_NODE_VERIFY_PTR_FUNC (current_node);

    const char *node_type_to_string = NULL;

    if (NODE_TYPE != LANGUAGE_OPERATOR || NODE_TYPE == NODE_TYPE_ERROR)
        return NULL;

    node_type_to_string = LangNodeOperatorToString ((current_node -> data -> nodeValue).langOperator);

    return node_type_to_string;
}

const char *LangNodeOperatorToString (const LangNodeOperator current_operator) {

    switch (current_operator) {
        case IF:
            return "IF";
            break;

        case WHILE:
            return "WHILE";
            break;

        case ELSE:
            return "ELSE";
            break;

        case ASSIGN:
            return "ASSIGN";
            break;

        case PRINT:
            return "PRINT";
            break;

        case END_LINE:
            return "LINE_END";
            break;

        case NEW_FUNC:
            return "NEW_FUNC";
            break;

        case FUNC:
            return "FUNC";
            break;

        case COMMA:
            return "COMMA";
            break;

        case FUNC_CALL:
            return "FUNC_CALL";
            break;

        case FUNC_RET:
            return "RETURN";
            break;

        case READ:
            return "READ";
            break;

        case FUNC_ARG:
            return "FUNC_ARG";
            break;

        case INIT:
            return "TYPE";
            break;

        case TYPE_INT:
            return "TYPE_INT";
            break;

        case AND:
            return "AND";
            break;

        case OR:
            return "OR";
            break;

        case OPEN_BRACE:
            return "OPEN_BRACE";
            break;

        case CLOSE_BRACE:
            return "CLOSE_BRACE";
            break;

        default:
            return NULL;
    }

    return NULL;
}

const char *MathNodeTypeToString (const TreeNode *current_node, const NameTable *name_table) {

    assert (current_node);
    assert (current_node -> data);

    const char *node_type_to_string = NULL;

    if (NODE_TYPE == LANGUAGE_OPERATOR || NODE_TYPE == NODE_TYPE_ERROR)
        return NULL;

    if (!(node_type_to_string = MathNodeNumVarEndToString (current_node, name_table)))
        node_type_to_string = MathNodeOperatorToString (current_node);

    return node_type_to_string;
}

const char *MathNodeNumVarEndToString (const TreeNode *current_node, const NameTable *name_table) {

    assert (current_node);
    assert (current_node -> data);

    switch (NODE_TYPE) {

        case NUMBER:
            return NumberToString (NODE_VALUE);
            break;

        case VARIABLE:
            return NameTableVariableFind ((size_t) NODE_VALUE, name_table);
            break;

        case END:
            return "END";
            break;

        default:
            return NULL;
    }

    return NULL;
}

const char *NumberToString (const double number) {

    static char number_to_string[MAX_NUMBER_LENGTH + 1] = {};

    memset (number_to_string, 0, MAX_NUMBER_LENGTH + 1);

    sprintf (number_to_string, "%.3lf", number);

    return number_to_string;
}

const char *MathNodeOperatorToString (const TreeNode *current_node) {

    assert (current_node);
    assert (current_node -> data);

    switch (NODE_MATH_OPERATOR) {

        case OPERATOR_ADD:
            return "ADD";
            break;

        case OPERATOR_SUB:
            return "SUB";
            break;

        case OPERATOR_DIV:
            return "DIV";
            break;

        case OPERATOR_MUL:
            return "MUL";
            break;

        case OPERATOR_POW:
            return "POW";
            break;

        case OPERATOR_SIN:
            return "sin";
            break;

        case OPERATOR_COS:
            return "cos";
            break;

        case OPERATOR_LN:
            return "ln";
            break;

        case OPERATOR_SQRT:
            return "SQRT";
            break;

        case OPERATOR_GREATER:
            return "GREATER";
            break;

        case OPERATOR_LESS:
            return "LESS";
            break;

        case OPERATOR_GREATER_EQ:
            return "GREATER_EQ";
            break;

        case OPERATOR_LESS_EQ:
            return "LESS_EQ";
            break;

        case OPERATOR_EQUAL:
            return "EQ";
            break;

        case OPERATOR_NOT_EQUAL:
            return "NOT_EQ";
            break;

        case OPERATOR_OPEN_PARENTHESIS:
            return "(";
            break;

        case OPERATOR_CLOSE_PARENTHESIS:
            return ")";
            break;

        default:
            return NULL;
    }

    return NULL;
}

double MathTreeCompute (const Tree *math_expression_tree, const double variable_value) {

    if (MathTreeVerify (math_expression_tree, __func__) != 0)
        return NAN;

    return MathTreeNodeCompute (math_expression_tree -> root, variable_value);
}

double MathTreeNodeCompute (const TreeNode *current_node, const double variable_value) {

    if (!current_node)
        return 0;

    if (MathTreeNodeVerify (current_node) != 0)
        return NAN;

    const double left_branch_value  = MathTreeNodeCompute (current_node -> left_branch,
                                                           variable_value);

    const double right_branch_value = MathTreeNodeCompute (current_node -> right_branch,
                                                           variable_value);

    return MathTreeNodeComputeOperatorResult (current_node, left_branch_value, right_branch_value,
                                              variable_value);
}

double MathTreeNodeComputeOperatorResult (const TreeNode *current_node,
                                          const double left_branch_node_value,
                                          const double right_branch_node_value,
                                          const double variable_value) {

    if (MathTreeNodeVerify (current_node) != 0)
        return NAN;

    switch (NODE_TYPE) {

        case NUMBER:
            return NODE_VALUE;

        case VARIABLE:
            return variable_value;

        case UNARY_OPERATOR:
            return MathTreeNodeUnaryCompute (left_branch_node_value, NODE_MATH_OPERATOR);

        case BINARY_OPERATOR:
            return MathTreeNodeBinaryCompute (right_branch_node_value, BRANCH_VALUE (right_branch),
                                              NODE_MATH_OPERATOR);

        case NODE_TYPE_ERROR:
        default:
            fprintf (stderr, "UNKNOWN ERROR WHILST COMPUTING VARIABLE OR NUMBER\n");
            return NAN;
    }

    return NAN;
}

double MathTreeNodeUnaryCompute (const double left_branch_value,
                                 const MathNodeOperator current_node_operator) {

    switch (current_node_operator) {

        case OPERATOR_LN:
            return log (left_branch_value);

        case OPERATOR_SIN:
            return sin (left_branch_value);

        case OPERATOR_COS:
            return cos (left_branch_value);

        case OPERATOR_SQRT:
            return sqrt (left_branch_value);

        default:
            break;
    }

    return NAN;
}

double MathTreeNodeBinaryCompute (const double left_branch_value, const double right_branch_value,
                                  const MathNodeOperator current_node_operator) {

    switch (current_node_operator) {

        case OPERATOR_ADD:
            return left_branch_value + right_branch_value;

        case OPERATOR_SUB:
            return left_branch_value - right_branch_value;

        case OPERATOR_MUL:
            return left_branch_value * right_branch_value;

         case OPERATOR_DIV:
            if (!IsZero (right_branch_value))
                return left_branch_value / right_branch_value;
            else
                break;

        case OPERATOR_POW:
            return pow (left_branch_value, right_branch_value);

        default:
            break;
    }

    return NAN;
}

unsigned int MathTreeVerify (const Tree *math_expression_tree,
                             const char* name_parent_func) {

    assert (name_parent_func);

    unsigned int errors_math_expression_tree = TreeVerify (math_expression_tree, name_parent_func);

    if (errors_math_expression_tree != 0)
        return errors_math_expression_tree;

    errors_math_expression_tree = MathTreeNodeVerify (math_expression_tree -> root);

    return errors_math_expression_tree;
}

unsigned int MathTreeNodeVerify (const TreeNode *math_expression_tree_node) {

    unsigned int errors_math_tree_node = TreeNodeVerify (math_expression_tree_node);

    if (errors_math_tree_node != 0)
        return errors_math_tree_node;

    errors_math_tree_node = MathTreeNodeChecker (math_expression_tree_node);

    return errors_math_tree_node;
}

unsigned int MathTreeNodeChecker (const TreeNode *current_node) {

    if (!current_node)
        return 0;

    unsigned int errors_in_node_and_subtree = 0; // = MathNodeTypeCheckError (current_node);

    if (errors_in_node_and_subtree)
        return errors_in_node_and_subtree;

    errors_in_node_and_subtree |= NodeBinaryOperatorCheckErrors (current_node) |
                                  NodeUnaryOperatorCheckErrors (current_node)  |
                                  NodeNumberCheckErrors (current_node);
                                  //NodeVariableCheckErrors (current_node)

    errors_in_node_and_subtree |= MathTreeNodeChecker (current_node -> left_branch);
    errors_in_node_and_subtree |= MathTreeNodeChecker (current_node -> right_branch);

    return errors_in_node_and_subtree;
}

/*
unsigned int MathNodeTypeCheckError (const TreeNode *current_node) {

    assert (current_node);

    unsigned int is_node_type_error = ((NODE_TYPE != NUMBER && NODE_TYPE != VARIABLE) &&
                                      IsOperatorUnaryOrBinary (NODE_MATH_OPERATOR) != NODE_TYPE);

    if (is_node_type_error)
        TREE_ERROR_SET_AND_PRINT (is_node_type_error, MATH_TREE_WRONG_NODE_TYPE);

    return is_node_type_error;
}
*/

unsigned int NodeBinaryOperatorCheckErrors (const TreeNode *current_node) {

    assert (current_node);

    unsigned int is_binary_operator_error = 0;

    is_binary_operator_error = (NODE_TYPE == BINARY_OPERATOR     &&
                               (!(current_node -> left_branch)   ||
                               !(current_node -> right_branch)));

    if (is_binary_operator_error)
        TREE_ERROR_SET_AND_PRINT (is_binary_operator_error, MATH_TREE_BINARY_OP_WRONG_BRANCH);

    return is_binary_operator_error;
}

unsigned int NodeUnaryOperatorCheckErrors (const TreeNode *current_node) {

    assert (current_node);

    int is_unary_operator_error = 0;

    is_unary_operator_error = (NODE_TYPE == UNARY_OPERATOR            &&
                              (((bool) (current_node -> left_branch)) ==
                              (bool) (current_node -> right_branch)));

    if (is_unary_operator_error)
        TREE_ERROR_SET_AND_PRINT (is_unary_operator_error, MATH_TREE_UNARY_OP_WRONG_BRANCHES);

    return is_unary_operator_error;
}

unsigned int NodeVariableCheckErrors (const TreeNode *current_node) {

    assert (current_node);

    unsigned int is_variable_error = (NODE_TYPE == VARIABLE           &&
                                     (((current_node -> left_branch)) ||
                                     (current_node -> right_branch)));

    if (is_variable_error)
        TREE_ERROR_SET_AND_PRINT (is_variable_error, MATH_TREE_VARIABLE_HAVE_BRANCHES);

    return is_variable_error;
}

unsigned int NodeNumberCheckErrors (const TreeNode *current_node) {

    assert (current_node);

    unsigned int is_number_error (current_node -> data -> nodeType == NUMBER &&
                                 (((current_node -> left_branch))            ||
                                 (current_node -> right_branch)));

    if (is_number_error)
        TREE_ERROR_SET_AND_PRINT (is_number_error, MATH_TREE_NUMBER_HAVE_BRANCH);

    return is_number_error;
}

TreeFuncStatus MathTreeNodeConstantsSimplify (TreeNode *current_node) {

    MATH_TREE_NODE_VERIFY (current_node, TREE);

    if (!(current_node -> left_branch) &&
        !(current_node -> right_branch))

        return TREE_FUNC_STATUS_FAIL;

    if (MathTreeNodeConstantsSimplify (current_node -> left_branch) == TREE_FUNC_STATUS_OK)
        return TREE_FUNC_STATUS_OK;

    if (MathTreeNodeConstantsSimplify (current_node -> right_branch) == TREE_FUNC_STATUS_OK)
        return TREE_FUNC_STATUS_OK;

    switch (NODE_TYPE) {

        case UNARY_OPERATOR:
//            MathTreeNodeUnaryOperatorSimplify (current_node);
            break;

        case BINARY_OPERATOR:
            return MathTreeNodeBinaryOperatorSimplify (current_node);

        case NUMBER:
        case VARIABLE:
            return TREE_FUNC_STATUS_FAIL;

        case NODE_TYPE_ERROR:
        default:
            fprintf (stderr, "UNKNOWN NODE TYPE ERROR\n"); //TODO make output to log file
            return TREE_FUNC_STATUS_FAIL;
    }

    return TREE_FUNC_STATUS_FAIL;
}

TreeFuncStatus MathTreeNodeBinaryOperatorSimplify (TreeNode *current_node) {

    MATH_TREE_NODE_VERIFY (current_node, TREE);

    if (BRANCH_TYPE (left_branch) == NUMBER && BRANCH_TYPE (right_branch) == NUMBER)
        return MathTreeNodeNumAndNumSimplify (current_node);

    if (IS_VALUE_EQUAL (0, left_branch) || IS_VALUE_EQUAL (0, right_branch))
        return MathTreeNodeSmthAndZeroSimplify (current_node);

    if (IS_VALUE_EQUAL (1, left_branch) || IS_VALUE_EQUAL (1, right_branch))
        return MathTreeNodeSmthAndOneSimplify (current_node);

    return TREE_FUNC_STATUS_FAIL;
}

TreeFuncStatus MathTreeNodeNumAndNumSimplify (TreeNode *current_node) {

    MATH_TREE_NODE_VERIFY (current_node, TREE);
    MATH_TREE_NODE_VERIFY (current_node -> left_branch, TREE);
    MATH_TREE_NODE_VERIFY (current_node -> right_branch, TREE);

    double value_after_simplify = NAN;

    value_after_simplify = MathTreeNodeBinaryCompute (BRANCH_VALUE (left_branch), BRANCH_VALUE (right_branch),
                                                      NODE_MATH_OPERATOR);

    TreeNode *temp_node = NUM_ (value_after_simplify);

    TreeNodeReplace (current_node, temp_node, sizeof (MathNode));

    free (temp_node);

    return TREE_FUNC_STATUS_OK;
}

TreeFuncStatus MathTreeNodeSmthAndZeroSimplify (TreeNode *current_node) {

    MATH_TREE_NODE_VERIFY (current_node, TREE);
    MATH_TREE_NODE_VERIFY (current_node -> left_branch, TREE);
    MATH_TREE_NODE_VERIFY (current_node -> right_branch, TREE);

    TreeNode *branch_non_zero_ptr = NULL;
    TreeNextBranch branch_non_zero = NODE_NO_BRANCH;

    if (IS_VALUE_EQUAL (0, left_branch)) {

        branch_non_zero_ptr = current_node -> right_branch;
        branch_non_zero     = NODE_RIGHT_BRANCH;
    }

    if (IS_VALUE_EQUAL (0, right_branch)) {

        branch_non_zero_ptr = current_node -> left_branch;
        branch_non_zero     = NODE_LEFT_BRANCH;
    }

    if (!branch_non_zero_ptr || branch_non_zero == NODE_NO_BRANCH) {

        fprintf (stderr, "UNKNOWN ERROR IN BINARY ZERO SIMPLIFY (zero child nodes wasn't found)\n");
        return TREE_FUNC_STATUS_FAIL;
    }

    TreeNode *temp_node = NULL;

    switch (NODE_MATH_OPERATOR) {

        case OPERATOR_SUB:
            if (branch_non_zero == NODE_RIGHT_BRANCH)
                return TREE_FUNC_STATUS_FAIL;
        //fallthrough
        case OPERATOR_ADD:
            temp_node = TreeNodeCopy (temp_node, branch_non_zero_ptr, sizeof (MathNode));
            break;

        case OPERATOR_DIV:
            if (branch_non_zero == NODE_LEFT_BRANCH) {

                fprintf (stderr, "ERROR IN BINARY DIV SIMPLIFY (division by 0)\n");
                return TREE_FUNC_STATUS_FAIL;
            }
        //fallthrough
        case OPERATOR_POW:
            if (branch_non_zero == NODE_LEFT_BRANCH) {

                temp_node = NUM_ (1);
                break;
            }
        //fallthrough
        case OPERATOR_MUL:
            temp_node = NUM_ (0);
            break;


        default:
            fprintf (stderr, "UNKNOWN ERROR IN BINARY ZERO SIMPLIFY (node type wasn't found)\n");
            return TREE_FUNC_STATUS_FAIL;
    }

    TreeNodeReplace (current_node, temp_node, sizeof (MathNode));

    free (temp_node);

    return TREE_FUNC_STATUS_OK;
}

TreeFuncStatus MathTreeNodeSmthAndOneSimplify (TreeNode *current_node) {

    MATH_TREE_NODE_VERIFY (current_node, TREE);
    MATH_TREE_NODE_VERIFY (current_node -> left_branch, TREE);
    MATH_TREE_NODE_VERIFY (current_node -> right_branch, TREE);

    TreeNode *branch_non_one_ptr = NULL;
    TreeNextBranch branch_non_one = NODE_NO_BRANCH;

    if (IS_VALUE_EQUAL (1, left_branch)) {

        branch_non_one_ptr = current_node -> right_branch;
        branch_non_one     = NODE_RIGHT_BRANCH;
    }

    if (IS_VALUE_EQUAL (1, right_branch)) {

        branch_non_one_ptr = current_node -> left_branch;
        branch_non_one     = NODE_LEFT_BRANCH;
    }

    TreeNode *temp_node = NULL;

    if (!branch_non_one_ptr || branch_non_one == NODE_NO_BRANCH) {

        fprintf (stderr, "UNKNOWN ERROR IN BINARY ONE SIMPLIFY (child nodes with one wasn't found)\n");
        return TREE_FUNC_STATUS_FAIL;
    }

    switch (NODE_MATH_OPERATOR) {

        case OPERATOR_MUL:
            temp_node = TreeNodeCopy (temp_node, branch_non_one_ptr, sizeof (MathNode));
            break;

        case OPERATOR_DIV:
            if (branch_non_one == NODE_RIGHT_BRANCH)
                return TREE_FUNC_STATUS_FAIL;

        //fallthrough
        case OPERATOR_POW:
            if (branch_non_one == NODE_LEFT_BRANCH)
                temp_node = TreeNodeCopy (temp_node, branch_non_one_ptr, sizeof (MathNode));

            else if (branch_non_one == NODE_RIGHT_BRANCH)
                temp_node = NUM_ (1);

            break;

        case OPERATOR_ADD:
        case OPERATOR_SUB:
            return TREE_FUNC_STATUS_FAIL;

        default:
            fprintf (stderr, "UNKNOWN ERROR OCCURED WHILST BINARY ONE SIMPLIFY\n");
            return TREE_FUNC_STATUS_FAIL;
    }

    TreeNodeReplace (current_node, temp_node, sizeof (MathNode));

    free (temp_node);

    return TREE_FUNC_STATUS_OK;
}

TreeFuncStatus NameTableCtor (NameTable *name_table) {

    assert (name_table);

    name_table -> name_table_cell = (NameTableCell *) calloc (DEFAULT_NAME_TABLE_SIZE, sizeof (NameTableCell));

    if (!(name_table -> name_table_cell))
        return TREE_FUNC_STATUS_FAIL;

    name_table -> table_size     = 0;
    name_table -> table_capacity = DEFAULT_NAME_TABLE_SIZE;

    NAME_TABLE_VERIFY (name_table, TREE);

    return TREE_FUNC_STATUS_OK;
}

TreeFuncStatus NameTableAdd (NameTable *name_table, const NameTableDef word_type,
                                                    const char *word_name,
                                                    const size_t word_number) {

    assert (word_name);

    NAME_TABLE_VERIFY (name_table, TREE);

    if (name_table -> table_size == name_table -> table_capacity) {

        NameTableRecalloc (name_table);
        NAME_TABLE_VERIFY (name_table, TREE);
    }

    (name_table -> name_table_cell)[name_table -> table_size].word_type = word_type;
    (name_table -> name_table_cell)[name_table -> table_size].word_name = strdup (word_name);
    (name_table -> name_table_cell)[name_table -> table_size].word_number = word_number;

    (name_table -> table_size)++;

    NAME_TABLE_VERIFY (name_table, TREE);

    return TREE_FUNC_STATUS_OK;
}

const char *NameTableVariableFind (const size_t variable_index, const NameTable *name_table) {

    assert (name_table);
    assert (name_table -> name_table_cell);

    for (size_t i = 0; i < name_table -> table_size; i++)
        if (variable_index == (name_table -> name_table_cell)[i].word_number &&
            (name_table -> name_table_cell)[i].word_type == NAME_TABLE_VARIABLE)

            return (name_table -> name_table_cell)[i].word_name;

    return NULL;
}

long long NameTableWordFind (const NameTable *name_table, const char *word_name,
                             const long long start_index) {

    assert (word_name);
    assert (name_table);
    assert (name_table -> name_table_cell);

    size_t start_pos_find = 0;

    if (start_index >= 0)
        start_pos_find = start_index;

    for (size_t i = start_pos_find; i < name_table -> table_size; i++)
        if (strcmp ((name_table -> name_table_cell)[i].word_name, word_name) == 0)
            return i;

    return -1;
}

const char *NameTableRepeatCheck (const NameTable *name_table) {

    if (NameTableVerify (name_table, __func__) != 0)
        return NULL;

    if (name_table -> table_size == 0)
        return NULL;

    for (size_t i = 0; i < name_table -> table_size - 1; i++) {

        const char *current_func_name = (name_table -> name_table_cell)[i].word_name;

        if (NameTableWordFind (name_table, current_func_name, i + 1) != -1) {

            return current_func_name;
        }
    }

    return NULL;
}

TreeFuncStatus NameTableRecalloc (NameTable *name_table) {

    NAME_TABLE_VERIFY (name_table, TREE);

    const size_t old_name_table_bytes = (name_table -> table_capacity) * sizeof (NameTableCell);
    const size_t new_name_table_bytes = old_name_table_bytes * NAME_TABLE_INCREASE_NUM;

    NameTableCell *table_data = name_table -> name_table_cell;
    table_data                = (NameTableCell *) realloc (table_data, new_name_table_bytes);

    NAME_TABLE_VERIFY (name_table, TREE);

    size_t cur_name_table_size = name_table -> table_size;

    memset (table_data + cur_name_table_size, 0, new_name_table_bytes - old_name_table_bytes);

    name_table -> table_capacity  *= NAME_TABLE_INCREASE_NUM;
    name_table -> name_table_cell  = table_data;

    return TREE_FUNC_STATUS_OK;
}

unsigned int NameTableVerify (const NameTable *name_table, const char *parent_func_name) {

    assert (parent_func_name);

    unsigned int errors_name_table = 0;

    LOG_PRINT (TREE_LOG_FILE, "From function %s:\n", parent_func_name);

    if (!name_table)
        NAME_TABLE_SET_AND_PRINT_ERROR (NAME_TABLE_NULL_PTR);

    if (!(name_table -> name_table_cell))
        NAME_TABLE_SET_AND_PRINT_ERROR (NAME_TABLE_CELL_NULL_PTR);

    if (errors_name_table == 0)
        LOG_PRINT (TREE_LOG_FILE, "No errors.\n");

    return errors_name_table;
}

TreeFuncStatus NameTableDtor (NameTable *name_table) {

    assert (name_table);

    for (size_t i = 0; i < (name_table -> table_size); i++)
        free ((name_table -> name_table_cell)[i].word_name);

    size_t name_table_cells_size_bytes = sizeof (NameTableCell) * (name_table -> table_size);
    memset (name_table -> name_table_cell, 0, name_table_cells_size_bytes);

    name_table -> table_size = 0;

    free (name_table -> name_table_cell);
    name_table -> name_table_cell = NULL;

    return TREE_FUNC_STATUS_OK;
}

TreeFuncStatus LangTreeNodeRead (FILE *file_for_read_tree, TreeNode **tree_node_for_fill,
                                 NameTable *name_table) {  //PREORDER

    assert (file_for_read_tree);
    assert (tree_node_for_fill);
    assert (name_table);

    if (IsBracketInFileStr (file_for_read_tree, '(') == false)
        return TreeNodeNilCheck (file_for_read_tree);

    ON_TREE_DEBUG (printf ("( "));

    *tree_node_for_fill = CreateTreeNode ();

    if (LangTreeNodeDataRead (file_for_read_tree, tree_node_for_fill, name_table) == TREE_FUNC_STATUS_FAIL)
        return TREE_FUNC_STATUS_FAIL;
    //recursion below

    if (LangTreeNodeRead (file_for_read_tree,
                          &((*tree_node_for_fill) -> left_branch), name_table) == TREE_FUNC_STATUS_FAIL)

        return TREE_FUNC_STATUS_FAIL;

    if (LangTreeNodeRead (file_for_read_tree,
                          &((*tree_node_for_fill) -> right_branch), name_table) == TREE_FUNC_STATUS_FAIL)

        return TREE_FUNC_STATUS_FAIL;

//    ON_TREE_DEBUG (printf ("|read two nodes|"));

    if (IsBracketInFileStr (file_for_read_tree, ')')) {

        ON_TREE_DEBUG (printf (")"));
        return TREE_FUNC_STATUS_OK;
    }

    return TREE_FUNC_STATUS_FAIL;
}

TreeFuncStatus TreeNodeNilCheck (FILE *file_for_node_nil_check) {

    assert (file_for_node_nil_check);

    char buf[NODE_READ_BUF_SIZE] = "";

    fscanf (file_for_node_nil_check, " %3s", buf);

    if (strcmp (buf, NIL) == 0) {

        ON_TREE_DEBUG (printf ("nil "));

        return TREE_FUNC_STATUS_OK;
    }

    ON_TREE_DEBUG (printf ("wtf, |%s|", buf));

    return TREE_FUNC_STATUS_FAIL;
}

TreeFuncStatus LangTreeNodeDataRead (FILE *file_for_read_node_data, TreeNode **tree_node_for_data_read,
                                     NameTable *name_table) {

    assert (file_for_read_node_data);
    assert (tree_node_for_data_read);
    assert (name_table);

    char buf[NODE_READ_BUF_SIZE] = "";

    if (fscanf (file_for_read_node_data, " %s", buf)) {

        if (strcmp ("EQ", buf) == 0)
            *tree_node_for_data_read = EQUAL_ (NULL, NULL);

        else if (strcmp ("NOT_EQ", buf) == 0)
            *tree_node_for_data_read = NOT_EQUAL_ (NULL, NULL);

        else if (strcmp ("GREATER", buf) == 0)
            *tree_node_for_data_read = GREATER_ (NULL, NULL);

        else if (strcmp ("LESS", buf) == 0)
            *tree_node_for_data_read = LESS_ (NULL, NULL);

        else if (strcmp ("GREATER_EQ", buf) == 0)
            *tree_node_for_data_read = GREATER_EQ_ (NULL, NULL);

        else if (strcmp ("LESS_EQ", buf) == 0)
            *tree_node_for_data_read = LESS_EQ_ (NULL, NULL);

        else if (strcmp ("OPEN_PARENTHESIS", buf) == 0)
            *tree_node_for_data_read = OPEN_PARENTHESIS_;

        else if (strcmp ("CLOSE_PARENTHESIS", buf) == 0)
            *tree_node_for_data_read = CLOSE_PARENTHESIS_;

        else if (strcmp ("PRINT", buf) == 0)
            *tree_node_for_data_read = PRINT_;

        else if (strcmp ("ASSIGN", buf) == 0)
            *tree_node_for_data_read = ASSIGN_;

        else if (strcmp ("LINE_END", buf) == 0)
            *tree_node_for_data_read = END_LINE_ (NULL);

        else if (strcmp ("INIT", buf) == 0)
            *tree_node_for_data_read = INIT_ (NULL, NULL);

        else if (strcmp ("TYPE_INT", buf) == 0)
            *tree_node_for_data_read = TYPE_INT_;

        else if (strcmp ("TYPE", buf) == 0)
            *tree_node_for_data_read = INIT_ (NULL, NULL);

        else if (strcmp ("IF", buf) == 0)
            *tree_node_for_data_read = IF_ (NULL);

        else if (strcmp ("WHILE", buf) == 0)
            *tree_node_for_data_read = WHILE_ (NULL);

        else if (strcmp ("READ", buf) == 0)
            *tree_node_for_data_read = READ_;

        else if (strcmp ("FUNC", buf) == 0)
            *tree_node_for_data_read = FUNC_ (NULL);

        else if (strcmp ("FUNC_CALL", buf) == 0)
            *tree_node_for_data_read = FUNC_CALL_ (NULL);

        else if (strcmp ("RETURN", buf) == 0)
            *tree_node_for_data_read = FUNC_RET_ (NULL);

        else if (strcmp ("NEW_FUNC", buf) == 0)
            *tree_node_for_data_read = NEW_FUNC_ (NULL);

        else if (strcmp ("COMMA", buf) == 0)
            *tree_node_for_data_read = COMMA_ (NULL, NULL);

        else if (strcmp ("AND", buf) == 0)
            *tree_node_for_data_read = AND_ (NULL, NULL);

        else if (strcmp ("OR", buf) == 0)
            *tree_node_for_data_read = OR_ (NULL, NULL);

        else if (strcmp ("ADD", buf) == 0)
            *tree_node_for_data_read = ADD_ (NULL, NULL);

        else if (strcmp ("SUB", buf) == 0)
            *tree_node_for_data_read = SUB_ (NULL, NULL);

        else if (strcmp ("MUL", buf) == 0)
            *tree_node_for_data_read = MUL_ (NULL, NULL);

        else if (strcmp ("DIV", buf) == 0)
            *tree_node_for_data_read = DIV_ (NULL, NULL);

        else if (strcmp ("POW", buf) == 0)
            *tree_node_for_data_read = POW_ (NULL, NULL);

        else if (strcmp ("SIN", buf) == 0)
            *tree_node_for_data_read = SIN_ (NULL);

        else if (strcmp ("COS", buf) == 0)
            *tree_node_for_data_read = COS_ (NULL);

        else if (strcmp ("LN", buf) == 0)
            *tree_node_for_data_read = LN_ (NULL);

        else if (strcmp ("SQRT", buf) == 0)
            *tree_node_for_data_read = SQRT_ (NULL);

        else if (CheckIfWordIsNumber   (buf, tree_node_for_data_read) ||
                 CheckIfWordIsVariable (buf, tree_node_for_data_read, name_table));
        //continue if num or var wasn't read successfully

        else {

            fprintf (stderr, "UNKNOWN NODE DATA '%s'\n", buf);
            return TREE_FUNC_STATUS_FAIL;
        }

        ON_TREE_DEBUG (NodeTypePrint (stderr, *tree_node_for_data_read, name_table));

        return TREE_FUNC_STATUS_OK;
    }

    ON_TREE_DEBUG (printf ("wtf happened in node data read"));

    return TREE_FUNC_STATUS_FAIL;
}

bool CheckIfWordIsNumber (char *word_to_check, TreeNode **current_node) {

    assert (word_to_check);
    assert (current_node);

    char *word_end_ptr = word_to_check;

    const double value = strtod (word_to_check, &word_end_ptr);

    if (*word_end_ptr == '\0') {

        *current_node = NUM_ (value);

        return true;
    }

    return false;
}

bool CheckIfWordIsVariable (const char *word_to_check, TreeNode **current_node, NameTable *name_table) {

    assert (word_to_check);
    assert (current_node);
    assert (name_table);

    static int number_of_variable = 0;

    if ((!isalpha (word_to_check[0]) || word_to_check[0] < 0) && word_to_check[0] != '_')
        return false;

    for (size_t i = 1; word_to_check[i]; i++)
        if ((!isalnum (word_to_check[i]) || word_to_check[0] < 0) && word_to_check[0] != '_')
            return false;

    *current_node = VAR_ (number_of_variable);

    NameTableAdd (name_table, NAME_TABLE_VARIABLE, word_to_check, number_of_variable);

    number_of_variable++;

    return true;
}

TreeFuncStatus LangTreeFilePrint (FILE *output_file, const Tree *lang_tree, const NameTable *name_table) {

    assert (output_file);
    assert (lang_tree);

    LangTreeNodeFilePrint (output_file, lang_tree -> root, name_table);

    return TREE_FUNC_STATUS_OK;
}

TreeFuncStatus LangTreeNodeFilePrint (FILE *output_file, const TreeNode *lang_tree_node,
                                      const NameTable *name_table) {

    assert (output_file);

    if (!lang_tree_node) {

        fprintf (output_file, "nil ");
        return TREE_FUNC_STATUS_OK;
    }

    MATH_TREE_NODE_VERIFY (lang_tree_node, TREE);

    fprintf (output_file, "(");

    NodeTypePrint (output_file, lang_tree_node, name_table);
    fprintf (output_file, " ");

    LangTreeNodeFilePrint (output_file, lang_tree_node -> left_branch, name_table);
    LangTreeNodeFilePrint (output_file, lang_tree_node -> right_branch, name_table);

    fprintf (output_file, ")");

    return TREE_FUNC_STATUS_OK;
}
