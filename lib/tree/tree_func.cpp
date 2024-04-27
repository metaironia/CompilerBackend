#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../mystacklib/my_stack_func.h"

#include "tree_func.h"
#include "tree_log.h"

extern FILE *TREE_LOG_FILE;

enum TreeFuncStatus TreeCtor (Tree *tree_to_create) {

    assert (tree_to_create);

    (tree_to_create -> root) = CreateTreeNode ();

    TREE_VERIFY (tree_to_create);

    return TREE_FUNC_STATUS_OK;
}

TreeNode *CreateTreeNode (void) {

    TreeNode *tree_node_ptr = (TreeNode *) calloc (1, sizeof (TreeNode));
    assert (tree_node_ptr);

    return tree_node_ptr;
}

enum TreeFuncStatus TreeNodeLeftBranchCreate (TreeNode *node_for_add_left_branch) {

    TREE_NODE_VERIFY (node_for_add_left_branch);

    (node_for_add_left_branch -> left_branch) = CreateTreeNode ();

    TREE_NODE_VERIFY (node_for_add_left_branch);

    return TREE_FUNC_STATUS_OK;
}

enum TreeFuncStatus TreeNodeRightBranchCreate (TreeNode *node_for_add_right_branch) {

    TREE_NODE_VERIFY (node_for_add_right_branch);

    (node_for_add_right_branch -> right_branch) = CreateTreeNode ();

    TREE_NODE_VERIFY (node_for_add_right_branch);

    return TREE_FUNC_STATUS_OK;
}

Tree *TreeCopy (Tree *copy_of_math_tree, const Tree *math_tree_for_copy, const size_t node_data_size) {

    assert (math_tree_for_copy);
    assert (copy_of_math_tree);

    TREE_VERIFY_PTR_FUNC (math_tree_for_copy);

    memset (copy_of_math_tree, 0, sizeof (Tree));

    TreeCtor (copy_of_math_tree);

    (copy_of_math_tree -> root) = TreeNodeCopy (copy_of_math_tree -> root, math_tree_for_copy -> root,
                                                node_data_size);

    return copy_of_math_tree;
}

TreeNode *TreeNodeCopy (TreeNode *copy_of_math_tree_node, const TreeNode *math_tree_node_for_copy,
                        const size_t node_data_size) {

    if (!math_tree_node_for_copy)
        return NULL;

    if (!copy_of_math_tree_node)
        copy_of_math_tree_node = CreateTreeNode ();

    assert (copy_of_math_tree_node);

    TreeNodeDataCopy (copy_of_math_tree_node, math_tree_node_for_copy, node_data_size);

    (copy_of_math_tree_node -> left_branch)  = TreeNodeCopy (copy_of_math_tree_node -> left_branch,
                                                             math_tree_node_for_copy -> left_branch,
                                                             node_data_size);

    (copy_of_math_tree_node -> right_branch) = TreeNodeCopy (copy_of_math_tree_node -> right_branch,
                                                             math_tree_node_for_copy -> right_branch,
                                                             node_data_size);

    return copy_of_math_tree_node;
}

TreeFuncStatus TreeNodeDataCopy (TreeNode *copy_of_math_tree_node, const TreeNode* math_tree_node,
                                 const size_t node_data_size) {

    assert (copy_of_math_tree_node);
    assert (math_tree_node);

    if (!copy_of_math_tree_node -> data)
        copy_of_math_tree_node -> data = (TreeElem_t) calloc (1, node_data_size);

    assert (copy_of_math_tree_node -> data);
    assert (math_tree_node -> data);

    memcpy (copy_of_math_tree_node -> data, math_tree_node -> data, node_data_size);

    return TREE_FUNC_STATUS_OK;
}

enum TreeFuncStatus TreeNodeReplace (TreeNode *tree_node_for_replace, TreeNode *tree_node_new,
                                     const size_t node_data_size) {

    assert (tree_node_for_replace);

    TREE_NODE_VERIFY (tree_node_for_replace);
    TREE_NODE_VERIFY (tree_node_new);

    TreeNode *temp_node = NULL;

    temp_node = TreeNodeCopy (temp_node, tree_node_new, node_data_size);

    TreeAllNodesDestruct (&tree_node_for_replace -> left_branch);
    TreeAllNodesDestruct (&tree_node_for_replace -> right_branch);

    TreeNodeCopy (tree_node_for_replace, temp_node, node_data_size);

    free (temp_node);
    temp_node = NULL;

    return TREE_FUNC_STATUS_OK;
}

//enum TreeFuncStatus TreeReadFromFile (FILE *file_with_tree, Tree *tree_for_fill) {
//
//    assert (file_with_tree);
//
//    TREE_VERIFY (tree_for_fill);
//
//    if (TreeNodeRead (file_with_tree, &(tree_for_fill -> root)) == TREE_FUNC_STATUS_FAIL) {
//
//        fprintf (stderr, "Database is incorrect.");
//
//        return TREE_FUNC_STATUS_FAIL;
//    }
//
//    TREE_VERIFY (tree_for_fill);
//
//    return TREE_FUNC_STATUS_OK;
//}
//


//enum TreeFuncStatus TreeOutputToFile (FILE *file_for_output_tree, const Tree *tree_for_output) {   //TODO output
//
//    TREE_VERIFY (tree_for_output);
//
//    assert (file_for_output_tree);
//
//    TreeNodeOutputToFile (file_for_output_tree, tree_for_output -> root);
//
//    return TREE_FUNC_STATUS_OK;
//}
//
//enum TreeFuncStatus TreeNodeOutputToFile (FILE *file_for_output_node,
//                                          const TreeNode *tree_node_for_output) {
//
//    assert (file_for_output_node);
//
//    if (!tree_node_for_output) {
//
//        fprintf (file_for_output_node, "nil ");
//
//        return TREE_FUNC_STATUS_OK;
//    }
//
//    TREE_NODE_VERIFY (tree_node_for_output);
//
//    fprintf (file_for_output_node, "( ");
//
//    if (IS_TREE_ELEM_STRING)
//        fprintf (file_for_output_node, "\"" TREE_DATA_FORMAT "\" ", tree_node_for_output -> data);
//
//    else
//        fprintf (file_for_output_node, TREE_DATA_FORMAT " ", tree_node_for_output -> data);
//
//    TreeNodeOutputToFile (file_for_output_node, tree_node_for_output -> left_branch);
//    TreeNodeOutputToFile (file_for_output_node, tree_node_for_output -> right_branch);
//
//    fprintf (file_for_output_node, ") ");
//
//    return TREE_FUNC_STATUS_OK;
//}

//enum TreeFuncStatus TreeElementFind (const Tree *tree_for_element_find, const TreeElem_t tree_data_to_find,
//                                     Stack *stack_tree_path) {
//
//    TREE_VERIFY (tree_for_element_find);
//
//    if (IS_TREE_ELEM_STRING)
//        assert (tree_data_to_find);
//
//    if (TreeNodeElementFind (tree_for_element_find -> root, tree_data_to_find,
//                             stack_tree_path) == TREE_FUNC_STATUS_OK)
//
//        return TREE_FUNC_STATUS_OK;
//
//    return TREE_FUNC_STATUS_FAIL;
//}
//
//enum TreeFuncStatus TreeNodeElementFind (const TreeNode *tree_node_for_element_find,
//                                         const TreeElem_t tree_node_data_to_find,
//                                         Stack *stack_tree_node_path) {
//
//    assert (stack_tree_node_path);
//
//    if (!tree_node_for_element_find)
//        return TREE_FUNC_STATUS_FAIL;
//
//    TREE_NODE_VERIFY (tree_node_for_element_find);
//
//    if (IS_TREE_ELEM_STRING)
//        assert (tree_node_data_to_find);
//
//    if (TreeCompareData (tree_node_for_element_find, tree_node_data_to_find) == TREE_FUNC_STATUS_OK)
//        return TREE_FUNC_STATUS_OK;
//
//    //recursion below
//
//    if (TreeNodeElementFind (tree_node_for_element_find -> left_branch,
//                             tree_node_data_to_find, stack_tree_node_path) == TREE_FUNC_STATUS_OK) {
//
//        StackPush (stack_tree_node_path, 1);   //TODO fix nums here
//
//        return TREE_FUNC_STATUS_OK;
//    }
//
//    if (TreeNodeElementFind (tree_node_for_element_find -> right_branch,
//                             tree_node_data_to_find, stack_tree_node_path) == TREE_FUNC_STATUS_OK) {
//
//        StackPush (stack_tree_node_path, 0);   //TODO fix nums here
//
//        return TREE_FUNC_STATUS_OK;
//    }
//
//    return TREE_FUNC_STATUS_FAIL;
//}

//enum TreeFuncStatus TreeCompareData (const TreeNode *tree_node_for_cmp_data,      //TODO compare math node
//                                     const TreeElem_t data_to_cmp) {
//
//    TREE_NODE_VERIFY (tree_node_for_cmp_data);
//
//    if (IS_TREE_ELEM_STRING)
//        assert (data_to_cmp);
//
//    if (IS_TREE_ELEM_STRING)  {
//
//        if (strcmp (data_to_cmp, tree_node_for_cmp_data -> data) == 0)
//            return TREE_FUNC_STATUS_OK;
//    }
//
//    else if (tree_node_for_cmp_data -> data == data_to_cmp)   //TODO compare double values
//        return TREE_FUNC_STATUS_OK;
//
//    return TREE_FUNC_STATUS_FAIL;
//}

unsigned int TreeVerify (const Tree *tree_for_verify, const char *name_parent_func) {

    assert (name_parent_func);

    unsigned int errors_in_tree = 0;

    LOG_PRINT (TREE_LOG_FILE, "From function %s:\n", name_parent_func);

    if (!tree_for_verify) {

        TREE_ERROR_SET_AND_PRINT (errors_in_tree, TREE_NULL_PTR);

        return errors_in_tree;
    }

    TreeNode *root_node = tree_for_verify -> root;

    errors_in_tree |= TreeNodeVerify (root_node);

    if (errors_in_tree == 0)
        LOG_PRINT (TREE_LOG_FILE, "No errors.\n");

    return errors_in_tree;
}

unsigned int TreeNodeVerify (const TreeNode *tree_node_for_verify) {

    unsigned int errors_in_tree_node = 0;

    if (!tree_node_for_verify) {

        TREE_ERROR_SET_AND_PRINT (errors_in_tree_node, TREE_NODE_NULL_PTR);

        return errors_in_tree_node;
    }

    if (TreeCycledNodeSearch (tree_node_for_verify) == TREE_FUNC_STATUS_FAIL)
        TREE_ERROR_SET_AND_PRINT (errors_in_tree_node, TREE_CYCLED_NODE);

    if (!(tree_node_for_verify -> data) &&
        ((tree_node_for_verify -> left_branch != NULL) || (tree_node_for_verify -> right_branch != NULL))) {

        TREE_ERROR_SET_AND_PRINT (errors_in_tree_node, TREE_NODE_DATA_NULL_PTR);

        return errors_in_tree_node;
    }

    if (TreeNodeFromPoisonSearch (tree_node_for_verify) == TREE_FUNC_STATUS_FAIL)
        TREE_ERROR_SET_AND_PRINT (errors_in_tree_node, BRANCH_FROM_POISON);

    return errors_in_tree_node;
}

enum TreeFuncStatus TreeCycledNodeSearch (const TreeNode *tree_node_for_cycle_search) {

    if (!tree_node_for_cycle_search)
        return TREE_FUNC_STATUS_OK;

    if (tree_node_for_cycle_search == tree_node_for_cycle_search -> left_branch ||
        tree_node_for_cycle_search == tree_node_for_cycle_search -> right_branch)

        return TREE_FUNC_STATUS_FAIL;

    //recursion below

    if (TreeCycledNodeSearch (tree_node_for_cycle_search -> left_branch)  == TREE_FUNC_STATUS_FAIL ||
        TreeCycledNodeSearch (tree_node_for_cycle_search -> right_branch) == TREE_FUNC_STATUS_FAIL)

        return TREE_FUNC_STATUS_FAIL;

    return TREE_FUNC_STATUS_OK;
}

enum TreeFuncStatus TreeNodeFromPoisonSearch (const TreeNode *tree_node_for_poison_search) {

    if (!tree_node_for_poison_search)
        return TREE_FUNC_STATUS_OK;

    if (IS_TREE_ELEM_POISON (tree_node_for_poison_search -> data) &&
        (tree_node_for_poison_search -> left_branch != NULL ||
        tree_node_for_poison_search -> right_branch != NULL))

        return TREE_FUNC_STATUS_FAIL;

    //recursion below

    if (TreeNodeFromPoisonSearch (tree_node_for_poison_search -> left_branch)  == TREE_FUNC_STATUS_FAIL ||
        TreeNodeFromPoisonSearch (tree_node_for_poison_search -> right_branch) == TREE_FUNC_STATUS_FAIL)

        return TREE_FUNC_STATUS_FAIL;

    return TREE_FUNC_STATUS_OK;
}

enum TreeFuncStatus TreeNodeClear (TreeNode *tree_node_for_destruct) {

    if (!tree_node_for_destruct)
        return TREE_FUNC_STATUS_OK;

    free (tree_node_for_destruct -> data);

    memset (&(tree_node_for_destruct -> data), 0, sizeof (TreeElem_t));

    return TREE_FUNC_STATUS_OK;
}

enum TreeFuncStatus TreeAllNodesDestruct (TreeNode **tree_node_for_destruct) {

    assert (tree_node_for_destruct);

    if (!(*tree_node_for_destruct))
        return TREE_FUNC_STATUS_OK;

    TreeAllNodesDestruct (&((*tree_node_for_destruct) -> left_branch));
    TreeAllNodesDestruct (&((*tree_node_for_destruct) -> right_branch));

    free ((*tree_node_for_destruct) -> data);

    memset (&((*tree_node_for_destruct) -> data), 0, sizeof (TreeElem_t));

    free (*tree_node_for_destruct);
    *tree_node_for_destruct = NULL;

    return TREE_FUNC_STATUS_OK;
}

enum TreeFuncStatus TreeDtor (Tree *tree_for_destruct) {

    if (!tree_for_destruct)
        return TREE_FUNC_STATUS_OK;

    TreeAllNodesDestruct (&(tree_for_destruct -> root));

    return TREE_FUNC_STATUS_OK;
}

bool IsBracketInFileStr (FILE *file_to_check_str, const char bracket_type) {

    assert (file_to_check_str);

    char scanned_bracket = '\0';

    fscanf (file_to_check_str, " %c", &scanned_bracket);

    if (scanned_bracket == bracket_type)
        return true;

    fseek (file_to_check_str, -1, SEEK_CUR);

    return false;
}

