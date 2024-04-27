#include <stdio.h>
#include <assert.h>

#include "../../lib/tree/tree_func.h"
#include "../../lib/tree/tree_log.h"

#include "../../lib/tree/math_tree/dsl_commands.h"
#include "../../lib/tree/math_tree/math_tree_func.h"

#include "backend.h"


BackendFuncStatus TreeToAsmFile (FILE *asm_file, const Tree *lang_tree) {

    assert (asm_file);
    assert (lang_tree);

    AsmFileBeginAndEnd (asm_file);

    AsmFileNewFuncWrite (asm_file, lang_tree -> root);

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileBeginAndEnd (FILE *asm_file) {

    assert (asm_file);

    fprintf (asm_file, "push 0\n"
                       "push 0\n"
                       "pop rbx\n"
                       "pop rdx\n"
                       "call main\n"
                       "hlt\n\n");

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileFuncNameWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    fprintf (asm_file, ":");
    fprintf (asm_file, "%s\n", (char *) ((size_t) NODE_VALUE));

    fprintf (asm_file, "push rbx\n"
                       "push rdx\n"
                       "pop rbx\n"
                       "push rdx\n"
                       "push 16\n"
                       "add\n"
                       "pop rdx\n");   // 16 variables in func is max

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileInitFuncArgsWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (!current_node)
        return BACKEND_FUNC_STATUS_OK;

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
                return BACKEND_FUNC_STATUS_FAIL;
        }

        fprintf (asm_file, "pop rcx\n");
        fprintf (asm_file, "pop [rbx+%zu]\n", (size_t) NODE_VALUE);
        fprintf (asm_file, "push rcx\n");

        current_node = current_arg_node;

        switch (NODE_LANG_OPERATOR) {

            case COMMA:
                return AsmFileInitFuncArgsWrite (asm_file, current_node -> left_branch);
                break;

            case INIT:
                return BACKEND_FUNC_STATUS_OK;

            default:
                return BACKEND_FUNC_STATUS_FAIL;
        }
    }

    return BACKEND_FUNC_STATUS_FAIL;
}

BackendFuncStatus AsmFileNewFuncWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

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
                return BACKEND_FUNC_STATUS_FAIL;
        }

        AsmFileFuncNameWrite     (asm_file, CURRENT_FUNC_NAME_NODE (func_node));
        AsmFileInitFuncArgsWrite (asm_file, CURRENT_FUNC_NAME_NODE (func_node) -> left_branch);
        AsmFileLangOperatorWrite (asm_file, CURRENT_FUNC_FIRST_END_LINE_NODE (func_node));


        fprintf (asm_file, "ret\n\n");      // because of Arman (declane)!!!!!

        switch (NODE_LANG_OPERATOR) {

            case NEW_FUNC:
                AsmFileNewFuncWrite (asm_file, current_node -> left_branch);
                break;

            case INIT:
                return BACKEND_FUNC_STATUS_OK;

            default:
                return BACKEND_FUNC_STATUS_FAIL;
        }
    }

    return BACKEND_FUNC_STATUS_FAIL;
}

BackendFuncStatus AsmFileLangOperatorWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    if (!current_node)
        return BACKEND_FUNC_STATUS_OK;

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (!(NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == END_LINE))
        return BACKEND_FUNC_STATUS_FAIL;

    const TreeNode *end_line_node = current_node;

    current_node = current_node -> left_branch;

    if (NODE_TYPE == LANGUAGE_OPERATOR)
        switch (NODE_LANG_OPERATOR) {

            case IF:
                AsmFileOperatorIfWrite (asm_file, current_node);
                break;

            case WHILE:
                AsmFileOperatorWhileWrite (asm_file, current_node);
                break;

            case INIT:
                current_node = current_node -> right_branch;
            //fallthrough
            case ASSIGN:
                AsmFileOperatorAssignWrite (asm_file, current_node);
                break;

            case FUNC_RET:
                AsmFileOperatorRetWrite (asm_file, current_node);
                break;

            case FUNC_CALL:
                AsmFileFuncCallWrite (asm_file, current_node -> left_branch);
                fprintf (asm_file, "pop rax\n");
                break;

            case PRINT:
                AsmFileOperatorPrintWrite (asm_file, current_node);
                break;

            case READ:
                AsmFileOperatorReadWrite (asm_file, current_node);
                break;

            default:
                return BACKEND_FUNC_STATUS_FAIL;
        }

    return AsmFileLangOperatorWrite (asm_file, end_line_node -> right_branch);
}

BackendFuncStatus AsmFileOperatorReadWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == READ) {

        fprintf (asm_file, "in\n");

        return BACKEND_FUNC_STATUS_OK;
    }

    return BACKEND_FUNC_STATUS_FAIL;
}

BackendFuncStatus AsmFileOperatorPrintWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == PRINT) {

        AsmFileMathExpressionWrite (asm_file, current_node -> left_branch);

        fprintf (asm_file, "out\n");

        return BACKEND_FUNC_STATUS_OK;
    }

    return BACKEND_FUNC_STATUS_FAIL;
}

BackendFuncStatus AsmFileOperatorRetWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == FUNC_RET) {

        AsmFileMathExpressionWrite (asm_file, current_node -> left_branch);

        fprintf (asm_file, "pop rax\n"
                           "push rbx\n"
                           "pop rdx\n"
                           "pop rbx\n"
                           "ret\n");

        return BACKEND_FUNC_STATUS_OK;
    }

    return BACKEND_FUNC_STATUS_FAIL;

}

BackendFuncStatus AsmFileOperatorIfWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    static size_t operator_if_number = 0;
    const  size_t curr_if_number     = operator_if_number;

    operator_if_number++;

    AsmFileOperatorOrAndWrite (asm_file, current_node -> left_branch);

    fprintf (asm_file, "push 0\n"
                       "je end_if_%zu\n", curr_if_number);

    current_node = current_node -> right_branch;

    AsmFileLangOperatorWrite (asm_file, current_node);

    fprintf (asm_file, ":end_if_%zu\n", curr_if_number);

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileOperatorWhileWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    static size_t operator_while_number = 0;
    const  size_t curr_while_number     = operator_while_number;

    operator_while_number++;

    fprintf (asm_file, ":while_%zu\n", curr_while_number);

    AsmFileOperatorOrAndWrite (asm_file, current_node -> left_branch);

    fprintf (asm_file, "push 0\n"
                       "je end_while_%zu\n", curr_while_number);

    AsmFileLangOperatorWrite (asm_file, current_node -> right_branch);

    fprintf (asm_file, "jmp while_%zu\n"
                       ":end_while_%zu\n",
                       curr_while_number, curr_while_number);

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileOperatorOrAndWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (NODE_TYPE == LANGUAGE_OPERATOR && (NODE_LANG_OPERATOR == OR || NODE_LANG_OPERATOR == AND)) {

        AsmFileOperatorOrAndWrite      (asm_file, current_node -> left_branch);

        AsmFileOperatorComparisonWrite (asm_file, current_node -> right_branch);
    }

    else
        return AsmFileOperatorComparisonWrite (asm_file, current_node);

    if (NODE_TYPE == LANGUAGE_OPERATOR)
        switch (NODE_LANG_OPERATOR) {

            case OR:
                fprintf (asm_file, "add\n");
                break;

            case AND:
                fprintf (asm_file, "mul\n");
                break;

            default:
                return BACKEND_FUNC_STATUS_FAIL;
        }

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileOperatorComparisonWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (NODE_TYPE == BINARY_OPERATOR) {

        if (NODE_MATH_OPERATOR == OPERATOR_GREATER ||
            NODE_MATH_OPERATOR == OPERATOR_LESS ||
            NODE_MATH_OPERATOR == OPERATOR_EQUAL ||
            NODE_MATH_OPERATOR == OPERATOR_NOT_EQUAL) {

            AsmFileMathExpressionWrite (asm_file, current_node -> left_branch);
            AsmFileMathExpressionWrite (asm_file, current_node -> right_branch);
        }

        else
            AsmFileMathExpressionWrite (asm_file, current_node);
    }

    else if (NODE_TYPE == NUMBER || NODE_TYPE == VARIABLE)
        AsmFileMathExpressionWrite (asm_file, current_node);

    else
        return BACKEND_FUNC_STATUS_FAIL;


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
                return BACKEND_FUNC_STATUS_FAIL;
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

    return BACKEND_FUNC_STATUS_OK;
}


BackendFuncStatus AsmFileConditionWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    return AsmFileOperatorOrAndWrite (asm_file, current_node);
}

BackendFuncStatus AsmFileOperatorAssignWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    AsmFileMathExpressionWrite (asm_file, current_node -> right_branch);

    current_node = current_node -> left_branch;
    fprintf (asm_file, "pop [rbx+%zu]\n", (size_t) NODE_VALUE);

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileMathExpressionWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    if (!current_node)
        return BACKEND_FUNC_STATUS_FAIL;

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    switch (NODE_TYPE) {

        case NUMBER:
        case VARIABLE:
            AsmFileVarOrNumWrite (asm_file, current_node);
            return BACKEND_FUNC_STATUS_OK;

        case LANGUAGE_OPERATOR:
            switch (NODE_LANG_OPERATOR) {

                case FUNC_CALL:
                    AsmFileFuncCallWrite (asm_file, current_node -> left_branch);
                    return BACKEND_FUNC_STATUS_OK;

                case READ:
                    AsmFileOperatorReadWrite (asm_file, current_node);
                    return BACKEND_FUNC_STATUS_OK;

                default:
                    return BACKEND_FUNC_STATUS_FAIL;
            }

        default:
            break;
    }

    switch (NODE_TYPE) {

        case BINARY_OPERATOR:
            if (AsmFileMathExpressionWrite (asm_file, current_node -> left_branch) == BACKEND_FUNC_STATUS_FAIL)
                return BACKEND_FUNC_STATUS_FAIL;

            if (AsmFileMathExpressionWrite (asm_file, current_node -> right_branch) == BACKEND_FUNC_STATUS_FAIL)
                return BACKEND_FUNC_STATUS_FAIL;

            break;

        case UNARY_OPERATOR:
            if (AsmFileMathExpressionWrite (asm_file, current_node -> left_branch) == BACKEND_FUNC_STATUS_FAIL)
                return BACKEND_FUNC_STATUS_FAIL;

            break;

        default:
            return BACKEND_FUNC_STATUS_OK;
    }

    if (AsmFileMathOperatorWrite (asm_file, current_node) == BACKEND_FUNC_STATUS_FAIL)
        return BACKEND_FUNC_STATUS_FAIL;

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileFuncCallWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (current_node -> left_branch)
        AsmFileFuncPassedArgsWrite (asm_file, current_node -> left_branch);

    fprintf (asm_file, "call %s\n", (char *) ((size_t) NODE_VALUE));
    fprintf (asm_file, "push rax\n");

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileFuncPassedArgsWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    if (!current_node)
        return BACKEND_FUNC_STATUS_OK;

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == COMMA) {

        AsmFileFuncPassedArgsWrite (asm_file, current_node -> left_branch);

        current_node = current_node -> right_branch;
    }

    if (AsmFileMathExpressionWrite (asm_file, current_node) == BACKEND_FUNC_STATUS_FAIL)
        return BACKEND_FUNC_STATUS_FAIL;

        //TODO make call_func as argument

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileVarOrNumWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (NODE_TYPE == NUMBER)
        fprintf (asm_file, "push %lf\n", NODE_VALUE);

    else if (NODE_TYPE == VARIABLE)
        fprintf (asm_file, "push [rbx+%zu]\n", (size_t) NODE_VALUE);

    else
        return BACKEND_FUNC_STATUS_FAIL;

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus AsmFileMathOperatorWrite (FILE *asm_file, const TreeNode *current_node) {

    assert (asm_file);

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    if (NODE_TYPE == BINARY_OPERATOR || NODE_TYPE == UNARY_OPERATOR)
        switch (NODE_MATH_OPERATOR) {

            case OPERATOR_ADD:
                fprintf (asm_file, "add\n");
                break;

            case OPERATOR_SUB:
                fprintf (asm_file, "sub\n");
                break;

            case OPERATOR_MUL:
                fprintf (asm_file, "mul\n");
                break;

            case OPERATOR_DIV:
                fprintf (asm_file, "div\n");
                break;

            case OPERATOR_SQRT:
                fprintf (asm_file, "sqrt\n");
                break;

            default:
                return BACKEND_FUNC_STATUS_FAIL;
        }

    else
        return BACKEND_FUNC_STATUS_FAIL;

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus LangTreeVarsSet (Tree *lang_tree, const NameTable *lang_name_table) {

    MATH_TREE_VERIFY (lang_tree, BACKEND, lang_name_table);

    NAME_TABLE_VERIFY (lang_name_table, BACKEND);

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
                return BACKEND_FUNC_STATUS_FAIL;
        }

        NODE_VALUE = (double) ((size_t) NameTableVariableFind ((size_t) NODE_VALUE, lang_name_table));

        LangFuncVarsSet (current_node -> left_branch, lang_name_table, &local_func_name_table);
        LangFuncVarsSet (current_node -> right_branch, lang_name_table, &local_func_name_table);

        current_node = current_func_node;

        switch (NODE_LANG_OPERATOR) {

            case NEW_FUNC:
                current_node = current_func_node -> left_branch;
                break;

            case INIT:
                return BACKEND_FUNC_STATUS_OK;

            default:
                break;
        }

        NameTableDtor (&local_func_name_table);
    }

    return BACKEND_FUNC_STATUS_OK;
}

BackendFuncStatus LangFuncVarsSet (TreeNode *current_node, const NameTable *lang_name_table,
                                   NameTable *local_func_name_table) {

    if (!current_node)
        return BACKEND_FUNC_STATUS_OK;

    MATH_TREE_NODE_VERIFY (current_node, BACKEND);

    NAME_TABLE_VERIFY (local_func_name_table, BACKEND);

    if (NODE_TYPE == VARIABLE) {

        const char *current_var_name = NameTableVariableFind ((size_t) NODE_VALUE, lang_name_table);
        long long current_var_index = NameTableWordFind (local_func_name_table, current_var_name, 0);

        if (current_var_index == -1) {

            current_var_index = local_func_name_table -> table_size;

            NameTableAdd (local_func_name_table, NAME_TABLE_VARIABLE, current_var_name, current_var_index);
        }

        NODE_VALUE = (double) current_var_index;

        return BACKEND_FUNC_STATUS_OK;
    }

    if (NODE_TYPE == LANGUAGE_OPERATOR && NODE_LANG_OPERATOR == FUNC_CALL) {

        current_node = current_node -> left_branch;
        NODE_VALUE   = (double) ((size_t) NameTableVariableFind ((size_t) NODE_VALUE, lang_name_table));    // polniy kal

        LangFuncVarsSet (current_node -> left_branch, lang_name_table, local_func_name_table);
    }

    else {

        LangFuncVarsSet (current_node -> left_branch, lang_name_table, local_func_name_table);
        LangFuncVarsSet (current_node -> right_branch, lang_name_table, local_func_name_table);
    }

    return BACKEND_FUNC_STATUS_OK;
}

