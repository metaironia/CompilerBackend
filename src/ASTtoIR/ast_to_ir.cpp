#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../../lib/tree/tree_func.h"
#include "../../lib/tree/tree_log.h"

#include "../../lib/tree/math_tree/dsl_commands.h"
#include "../../lib/tree/math_tree/math_tree_func.h"

#include "ast_to_ir.h"
#include "ir_dsl.h"

IntReprFuncStatus IntReprCtor (IntRepr *interm_repr) {

    assert (interm_repr);

    IR_SIZE_     = 0;
    IR_CAPACITY_ = IR_DEFAULT_CAPACITY;

    IntReprDataCtor (interm_repr);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprDataCtor (IntRepr *interm_repr) {

    IR_CELL_ = (IntReprCell *) calloc (IR_CAPACITY_, sizeof (IntReprCell));
    assert (IR_CELL_);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprDataDtor (IntRepr *interm_repr) {

    assert (interm_repr);

    free (IR_CELL_);
    IR_CELL_ = NULL;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprDtor (IntRepr *interm_repr) {

    assert (interm_repr);

    IntReprDataDtor (interm_repr);

    IR_SIZE_     = 0;
    IR_CAPACITY_ = 0;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprDataRecalloc (IntRepr *interm_repr) {

    assert (interm_repr);

    const size_t all_cells_new_size = sizeof (IntReprCell) * (IR_INCREASE_NUM * IR_CAPACITY_); 
    const size_t all_cells_old_size = sizeof (IntReprCell) * IR_CAPACITY_;

    IR_CELL_ = (IntReprCell *) realloc (IR_CELL_, all_cells_new_size);

    memset (IR_CELL_, 0, all_cells_new_size - all_cells_old_size);

    IR_CAPACITY_ *= IR_INCREASE_NUM;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprEmit (IntRepr *interm_repr, 
                               const char        *cmd_name,          const CommandType cmd_type,
                               const OperandType  dest_operand_type, const int64_t     dest_operand_value,
                               const int64_t      dest_operand_disp, const bool        is_dest_operand_mem,
                               const OperandType  src_operand_type,  const int64_t     src_operand_value,
                               const int64_t      src_operand_disp,  const bool        is_src_operand_mem,
                                     IntReprCell *jump_ptr,          const int64_t     jump_addr,
                               const bool         need_patch) {

    assert (interm_repr);

    if (IR_SIZE_ >= IR_CAPACITY_)
        IntReprDataRecalloc (interm_repr);

    IR_TOP_CELL_ -> cmd_name = cmd_name;
    IR_TOP_CELL_ -> cmd_type = cmd_type;

    IR_TOP_CELL_ -> dest_operand_type   = dest_operand_type;  
    IR_TOP_CELL_ -> dest_operand_value  = dest_operand_value;
    IR_TOP_CELL_ -> dest_operand_disp   = dest_operand_disp;
    IR_TOP_CELL_ -> is_dest_operand_mem = is_dest_operand_mem;

    IR_TOP_CELL_ -> src_operand_type   = src_operand_type;
    IR_TOP_CELL_ -> src_operand_value  = src_operand_value;
    IR_TOP_CELL_ -> src_operand_disp   = src_operand_disp;
    IR_TOP_CELL_ -> is_src_operand_mem = is_src_operand_mem;

    IR_TOP_CELL_ -> jump_ptr   = jump_ptr;
    IR_TOP_CELL_ -> jump_addr  = jump_addr;
    IR_TOP_CELL_ -> need_patch = need_patch;

    IR_SIZE_++;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus TreeToIntRepr (FILE *asm_file, const Tree *lang_tree) {

    assert (asm_file);
    assert (lang_tree);

    IntReprBeginAndEnd (asm_file);

    IntReprNewFuncWrite (asm_file, lang_tree -> root);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprBeginAndEnd (FILE *asm_file) {

    assert (asm_file);

    fprintf (asm_file, "push 0\n"
                       "push 0\n"
                       "pop rbx\n"
                       "pop rdx\n"
                       "call main\n"
                       "hlt\n\n");

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprFuncNameWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    fprintf (asm_file, ":");
    fprintf (asm_file, "%s\n", (char *) ((size_t) NODE_VALUE));

    fprintf (asm_file, "push rbx\n"
                       "push rdx\n"
                       "pop rbx\n"
                       "push rdx\n"
                       "push 16\n"
                       "add\n"
                       "pop rdx\n");   // 16 variables in func is max

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprInitFuncArgsWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (!current_node)
        return IR_FUNC_STATUS_OK;

    const TreeNode *current_arg_node = current_node;

    if (NODE_TYPE == LANGUAGE_OPERATOR) {

        switch (NODE_LANG_OPERATOR) {

            case COMMA:
                current_node = current_node -> right_branch;
            //fallthrough
            case INIT:
                current_node = current_node -> right_branch;
                break;

            default:
                return IR_FUNC_STATUS_FAIL;
        }

        fprintf (asm_file, "pop rcx\n");
        fprintf (asm_file, "pop [rbx+%zu]\n", (size_t) NODE_VALUE);
        fprintf (asm_file, "push rcx\n");

        current_node = current_arg_node;

        switch (NODE_LANG_OPERATOR) {

            case COMMA:
                return IntReprInitFuncArgsWrite (asm_file, current_node -> left_branch);
                break;

            case INIT:
                return IR_FUNC_STATUS_OK;

            default:
                return IR_FUNC_STATUS_FAIL;
        }
    }

    return IR_FUNC_STATUS_FAIL;
}

IntReprFuncStatus IntReprNewFuncWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (NODE_TYPE == LANGUAGE_OPERATOR) {

        const TreeNode *func_node = NULL;

        switch (NODE_LANG_OPERATOR) {

            case NEW_FUNC:
                func_node = current_node -> right_branch;
                break;

            case INIT:
                func_node = current_node;
                break;

            default:
                return IR_FUNC_STATUS_FAIL;
        }

        IntReprFuncNameWrite     (asm_file, CURRENT_FUNC_NAME_NODE (func_node));
        IntReprInitFuncArgsWrite (asm_file, CURRENT_FUNC_NAME_NODE (func_node) -> left_branch);
        IntReprLangOperatorWrite (asm_file, CURRENT_FUNC_FIRST_END_LINE_NODE (func_node));


        fprintf (asm_file, "ret\n\n");      // because of Arman (declane)!!!!!

        switch (NODE_LANG_OPERATOR) {

            case NEW_FUNC:
                IntReprNewFuncWrite (asm_file, current_node -> left_branch);
                break;

            case INIT:
                return IR_FUNC_STATUS_OK;

            default:
                return IR_FUNC_STATUS_FAIL;
        }
    }

    return IR_FUNC_STATUS_FAIL;
}

IntReprFuncStatus IntReprLangOperatorWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    if (!current_node)
        return IR_FUNC_STATUS_OK;

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (!(NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == END_LINE))
        return IR_FUNC_STATUS_FAIL;

    const TreeNode *end_line_node = current_node;

    current_node = current_node -> left_branch;

    if (NODE_TYPE == LANGUAGE_OPERATOR)
        switch (NODE_LANG_OPERATOR) {

            case IF:
                IntReprOperatorIfWrite (asm_file, current_node);
                break;

            case WHILE:
                IntReprOperatorWhileWrite (asm_file, current_node);
                break;

            case INIT:
                current_node = current_node -> right_branch;
            //fallthrough
            case ASSIGN:
                IntReprOperatorAssignWrite (asm_file, current_node);
                break;

            case FUNC_RET:
                IntReprOperatorRetWrite (asm_file, current_node);
                break;

            case FUNC_CALL:
                IntReprFuncCallWrite (asm_file, current_node -> left_branch);
                fprintf (asm_file, "pop rax\n");
                break;

            case PRINT:
                IntReprOperatorPrintWrite (asm_file, current_node);
                break;

            case READ:
                IntReprOperatorReadWrite (asm_file, current_node);
                break;

            default:
                return IR_FUNC_STATUS_FAIL;
        }

    return IntReprLangOperatorWrite (asm_file, end_line_node -> right_branch);
}

IntReprFuncStatus IntReprOperatorReadWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == READ) {

        fprintf (asm_file, "in\n");

        return IR_FUNC_STATUS_OK;
    }

    return IR_FUNC_STATUS_FAIL;
}

IntReprFuncStatus IntReprOperatorPrintWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == PRINT) {

        IntReprMathExpressionWrite (asm_file, current_node -> left_branch);

        fprintf (asm_file, "out\n");

        return IR_FUNC_STATUS_OK;
    }

    return IR_FUNC_STATUS_FAIL;
}

IntReprFuncStatus IntReprOperatorRetWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == FUNC_RET) {

        IntReprMathExpressionWrite (asm_file, current_node -> left_branch);

        fprintf (asm_file, "pop rax\n"
                           "push rbx\n"
                           "pop rdx\n"
                           "pop rbx\n"
                           "ret\n");

        return IR_FUNC_STATUS_OK;
    }

    return IR_FUNC_STATUS_FAIL;

}

IntReprFuncStatus IntReprOperatorIfWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    static size_t operator_if_number = 0;
    const  size_t curr_if_number     = operator_if_number;

    operator_if_number++;

    IntReprOperatorOrAndWrite (asm_file, current_node -> left_branch);

    fprintf (asm_file, "push 0\n"
                       "je end_if_%zu\n", curr_if_number);

    current_node = current_node -> right_branch;

    IntReprLangOperatorWrite (asm_file, current_node);

    fprintf (asm_file, ":end_if_%zu\n", curr_if_number);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprOperatorWhileWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    static size_t operator_while_number = 0;
    const  size_t curr_while_number     = operator_while_number;

    operator_while_number++;

    fprintf (asm_file, ":while_%zu\n", curr_while_number);

    IntReprOperatorOrAndWrite (asm_file, current_node -> left_branch);

    fprintf (asm_file, "push 0\n"
                       "je end_while_%zu\n", curr_while_number);

    IntReprLangOperatorWrite (asm_file, current_node -> right_branch);

    fprintf (asm_file, "jmp while_%zu\n"
                       ":end_while_%zu\n",
                       curr_while_number, curr_while_number);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprOperatorOrAndWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (NODE_TYPE == LANGUAGE_OPERATOR && (NODE_LANG_OPERATOR == OR || NODE_LANG_OPERATOR == AND)) {

        IntReprOperatorOrAndWrite      (asm_file, current_node -> left_branch);

        IntReprOperatorComparisonWrite (asm_file, current_node -> right_branch);
    }

    else
        return IntReprOperatorComparisonWrite (asm_file, current_node);

    if (NODE_TYPE == LANGUAGE_OPERATOR)
        switch (NODE_LANG_OPERATOR) {

            case OR:
                fprintf (asm_file, "add\n");
                break;

            case AND:
                fprintf (asm_file, "mul\n");
                break;

            default:
                return IR_FUNC_STATUS_FAIL;
        }

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprOperatorComparisonWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (NODE_TYPE == BINARY_OPERATOR) {

        if (NODE_MATH_OPERATOR == OPERATOR_GREATER ||
            NODE_MATH_OPERATOR == OPERATOR_LESS ||
            NODE_MATH_OPERATOR == OPERATOR_EQUAL ||
            NODE_MATH_OPERATOR == OPERATOR_NOT_EQUAL) {

            IntReprMathExpressionWrite (asm_file, current_node -> left_branch);
            IntReprMathExpressionWrite (asm_file, current_node -> right_branch);
        }

        else
            IntReprMathExpressionWrite (asm_file, current_node);
    }

    else if (NODE_TYPE == NUMBER || NODE_TYPE == VARIABLE)
        IntReprMathExpressionWrite (asm_file, current_node);

    else
        return IR_FUNC_STATUS_FAIL;


    if (NODE_TYPE == BINARY_OPERATOR)
        switch (NODE_MATH_OPERATOR) {

            case OPERATOR_GREATER:
                fprintf (asm_file, "jb ");
                break;

            case OPERATOR_LESS:
                fprintf (asm_file, "ja ");
                break;

            case OPERATOR_GREATER_EQ:
                fprintf (asm_file, "jbe ");
                break;

            case OPERATOR_LESS_EQ:
                fprintf (asm_file, "jae ");
                break;

            case OPERATOR_EQUAL:
                fprintf (asm_file, "je ");
                break;

            case OPERATOR_NOT_EQUAL:
                fprintf (asm_file, "jne ");
                break;

            default:
                return IR_FUNC_STATUS_FAIL;
        }

    static size_t comparison_num = 0;

    fprintf (asm_file, "comparison_%zu\n"
                       "push 0\n"
                       "jmp comparison_end_%zu\n"
                       ":comparison_%zu\n"
                       "push 1\n"
                       ":comparison_end_%zu\n",
                        comparison_num, comparison_num, comparison_num, comparison_num);

    comparison_num++;

    return IR_FUNC_STATUS_OK;
}


IntReprFuncStatus IntReprConditionWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    return IntReprOperatorOrAndWrite (asm_file, current_node);
}

IntReprFuncStatus IntReprOperatorAssignWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    IntReprMathExpressionWrite (asm_file, current_node -> right_branch);

    current_node = current_node -> left_branch;
    fprintf (asm_file, "pop [rbx+%zu]\n", (size_t) NODE_VALUE);

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprMathExpressionWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    if (!current_node)
        return IR_FUNC_STATUS_FAIL;

    MATH_TREE_NODE_VERIFY (current_node, IR);

    switch (NODE_TYPE) {

        case NUMBER:
        case VARIABLE:
            IntReprVarOrNumWrite (asm_file, current_node);
            return IR_FUNC_STATUS_OK;

        case LANGUAGE_OPERATOR:
            switch (NODE_LANG_OPERATOR) {

                case FUNC_CALL:
                    IntReprFuncCallWrite (asm_file, current_node -> left_branch);
                    return IR_FUNC_STATUS_OK;

                case READ:
                    IntReprOperatorReadWrite (asm_file, current_node);
                    return IR_FUNC_STATUS_OK;

                default:
                    return IR_FUNC_STATUS_FAIL;
            }

        default:
            break;
    }

    switch (NODE_TYPE) {

        case BINARY_OPERATOR:
            if (IntReprMathExpressionWrite (asm_file, current_node -> left_branch) == IR_FUNC_STATUS_FAIL)
                return IR_FUNC_STATUS_FAIL;

            if (IntReprMathExpressionWrite (asm_file, current_node -> right_branch) == IR_FUNC_STATUS_FAIL)
                return IR_FUNC_STATUS_FAIL;

            break;

        case UNARY_OPERATOR:
            if (IntReprMathExpressionWrite (asm_file, current_node -> left_branch) == IR_FUNC_STATUS_FAIL)
                return IR_FUNC_STATUS_FAIL;

            break;

        default:
            return IR_FUNC_STATUS_OK;
    }

    //if (IntReprMathOperatorWrite (asm_file, current_node) == IR_FUNC_STATUS_FAIL)
    //    return IR_FUNC_STATUS_FAIL;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprFuncCallWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (current_node -> left_branch)
        IntReprFuncPassedArgsWrite (asm_file, current_node -> left_branch);

    fprintf (asm_file, "call %s\n", (char *) ((size_t) NODE_VALUE));
    fprintf (asm_file, "push rax\n");

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprFuncPassedArgsWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    if (!current_node)
        return IR_FUNC_STATUS_OK;

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == COMMA) {

        IntReprFuncPassedArgsWrite (asm_file, current_node -> left_branch);

        current_node = current_node -> right_branch;
    }

    if (IntReprMathExpressionWrite (asm_file, current_node) == IR_FUNC_STATUS_FAIL)
        return IR_FUNC_STATUS_FAIL;

        //TODO make call_func as argument

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprVarOrNumWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    if (NODE_TYPE == NUMBER)
        fprintf (asm_file, "push %lf\n", NODE_VALUE);

    else if (NODE_TYPE == VARIABLE)
        fprintf (asm_file, "push [rbx+%zu]\n", (size_t) NODE_VALUE);

    else
        return IR_FUNC_STATUS_FAIL;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprMathOperatorWrite (IntRepr *interm_repr, const TreeNode *current_node) {

    assert (interm_repr);

    MATH_TREE_NODE_VERIFY (current_node, IR);

    IR_TOP_CELL_ -> cmd_name          = "mov";
    IR_TOP_CELL_ -> cmd_type          = IR_CMD_MOV;
    IR_TOP_CELL_ -> dest_operand_type = IR_OP_REG_R13; 
    IR_TOP_CELL_ -> dest_operand_type = IR_OP_REG_R13;

    if (NODE_TYPE == BINARY_OPERATOR || NODE_TYPE == UNARY_OPERATOR)
        switch (NODE_MATH_OPERATOR) {

            case OPERATOR_ADD:
                //fprintf (asm_file, "add\n");
                break;

            case OPERATOR_SUB:
                //fprintf (asm_file, "sub\n");
                break;

            case OPERATOR_MUL:
                //fprintf (asm_file, "mul\n");
                break;

            case OPERATOR_DIV:
                //fprintf (asm_file, "div\n");
                break;

            case OPERATOR_SQRT:
                //fprintf (asm_file, "sqrt\n");
                break;

            default:
                return IR_FUNC_STATUS_FAIL;
        }

    else
        return IR_FUNC_STATUS_FAIL;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus LangTreeVarsSet (Tree *lang_tree, const NameTable *lang_name_table) {

    MATH_TREE_VERIFY  (lang_tree,       IR, lang_name_table);
    NAME_TABLE_VERIFY (lang_name_table, IR);

    TreeNode *current_node = lang_tree -> root;

    while (current_node && NODE_TYPE == LANGUAGE_OPERATOR) {

        NameTable local_func_name_table = {};
        NameTableCtor (&local_func_name_table);

        TreeNode *current_func_node = current_node;

        switch (NODE_LANG_OPERATOR) {

            case NEW_FUNC:
                current_node = CURRENT_FUNC_NAME_NODE (current_node -> right_branch);
                break;

            case INIT:
                current_node = CURRENT_FUNC_NAME_NODE (current_node);
                break;

            default:
                return IR_FUNC_STATUS_FAIL;
        }

        NODE_VALUE = (double) ((size_t) NameTableVariableFind ((size_t) NODE_VALUE, lang_name_table));

        LangFuncVarsSet (current_node -> left_branch,  lang_name_table, &local_func_name_table);
        LangFuncVarsSet (current_node -> right_branch, lang_name_table, &local_func_name_table);

        current_node = current_func_node;

        switch (NODE_LANG_OPERATOR) {

            case NEW_FUNC:
                current_node = current_func_node -> left_branch;
                break;

            case INIT:
                return IR_FUNC_STATUS_OK;

            default:
                break;
        }

        NameTableDtor (&local_func_name_table);
    }

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus LangFuncVarsSet (TreeNode *current_node, const NameTable *lang_name_table,
                                   NameTable *local_func_name_table) {

    if (!current_node)
        return IR_FUNC_STATUS_OK;

    MATH_TREE_NODE_VERIFY (current_node,          IR);
    NAME_TABLE_VERIFY     (local_func_name_table, IR);

    if (NODE_TYPE == VARIABLE) {

        const char *current_var_name  = NameTableVariableFind ((size_t) NODE_VALUE,   lang_name_table);
        long long   current_var_index = NameTableWordFind     (local_func_name_table, current_var_name, 0);

        if (current_var_index == -1) {

            current_var_index = local_func_name_table -> table_size;

            NameTableAdd (local_func_name_table, NAME_TABLE_VARIABLE, current_var_name, current_var_index);
        }

        NODE_VALUE = (double) current_var_index;

        return IR_FUNC_STATUS_OK;
    }

    if (NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == FUNC_CALL) {

        current_node = current_node -> left_branch;
        NODE_VALUE   = (double) ((size_t) NameTableVariableFind ((size_t) NODE_VALUE, lang_name_table));    // polniy kal

        LangFuncVarsSet (current_node -> left_branch, lang_name_table, local_func_name_table);
    }

    else {

        LangFuncVarsSet (current_node -> left_branch,  lang_name_table, local_func_name_table);
        LangFuncVarsSet (current_node -> right_branch, lang_name_table, local_func_name_table);
    }

    return IR_FUNC_STATUS_OK;
}

