#ifndef TREE_FUNC_H
#define TREE_FUNC_H

#include "../mystacklib/my_stack_func.h"
#include "math_tree/math_tree_node_data.h"


#define NIL                     "nil"

#ifndef TREE_DATA_FORMAT
    #define TREE_DATA_FORMAT    "%s"
#endif

#define DEBUG_TREE               0

#if DEBUG_TREE
    #define ON_TREE_DEBUG(...)   {__VA_ARGS__;}
#else
    #define ON_TREE_DEBUG(...)
#endif

#define TREE_VERIFY(tree)   {                                                   \
                                if (TreeVerify (tree, __func__) != 0)           \
                                    return TREE_FUNC_STATUS_FAIL;               \
                            }

#define TREE_VERIFY_PTR_FUNC(tree)                                              \
                            {                                                   \
                                if (TreeVerify (tree, __func__) != 0)           \
                                    return NULL;                                \
                            }

#define TREE_NODE_VERIFY(tree_node)                                  \
                            {                                        \
                                if (TreeNodeVerify (tree_node) != 0) \
                                    return TREE_FUNC_STATUS_FAIL;    \
                            }

typedef MathNode* TreeElem_t;

#define IS_TREE_ELEM_STRING 0

/// 1 if tree element type is floating point number, 0 if not.
#define IS_TREE_ELEM_FLOAT  0

#define IS_TREE_ELEM_PTR    1

/// Defines how to check if tree element is poison number.
#if IS_TREE_ELEM_FLOAT

    const TreeElem_t TREE_POISON_NUM = NAN;                  m///< Poison number if tree element type is floating point.
    #define IS_TREE_ELEM_POISON(x)  isnan ((float) x)        ///< Method to check if tree element is poison.
#else

    #if IS_TREE_ELEM_PTR
        const TreeElem_t TREE_POISON_NUM = NULL;             ///< Poison number if tree element type is pointer.
    #else
        const TreeElem_t TREE_POISON_NUM = 0xDEAD;           ///< Poison number if tree element type is integer.
    #endif

    #define IS_TREE_ELEM_POISON(x)  (x == TREE_POISON_NUM)   ///< Method to check if tree element is poison.
#endif

const int NODE_READ_BUF_SIZE = 100;

struct TreeNode {

    TreeElem_t data;

    TreeNode *left_branch;
    TreeNode *right_branch;
};

struct Tree {

    TreeNode *root;
};

enum TreeFuncStatus {

    TREE_FUNC_STATUS_OK,
    TREE_FUNC_STATUS_FAIL
};

enum TreeErrors {

    TREE_NULL_PTR = (1 << 0),
    TREE_NODE_NULL_PTR = (1 << 1),
    TREE_NODE_DATA_NULL_PTR = (1 << 2),
    TREE_CYCLED_NODE = (1 << 3),
    BRANCH_FROM_POISON = (1 << 4),
    MATH_TREE_NUMBER_HAVE_BRANCH = (1 << 5),
    MATH_TREE_BINARY_OP_WRONG_BRANCH = (1 << 6),
    MATH_TREE_UNARY_OP_WRONG_BRANCHES = (1 << 7),
    MATH_TREE_VARIABLE_HAVE_BRANCHES = (1 << 8),
    MATH_TREE_WRONG_NODE_TYPE = (1 << 9)
};

enum TreeNextBranch {

    NODE_LEFT_BRANCH = 1,
    NODE_RIGHT_BRANCH = 0,
    NODE_NO_BRANCH = -1
};

enum TreeFuncStatus TreeCtor (Tree *tree_to_create);

TreeNode *CreateTreeNode (void);

enum TreeFuncStatus TreeNodeLeftBranchCreate (TreeNode *node_for_add_left_branch);

enum TreeFuncStatus TreeNodeRightBranchCreate (TreeNode *node_for_add_right_branch);

Tree *TreeCopy (Tree *copy_of_math_tree, const Tree *math_tree_for_copy, const size_t node_data_size);

TreeNode *TreeNodeCopy (TreeNode *copy_of_math_tree_node, const TreeNode *math_tree_node_for_copy,
                        const size_t node_data_size);

TreeFuncStatus TreeNodeDataCopy (TreeNode *copy_of_math_tree_node, const TreeNode* math_tree_node,
                                 const size_t node_data_size);

enum TreeFuncStatus TreeNodeReplace (TreeNode *tree_node_for_replace, TreeNode *tree_node_new,
                                     const size_t node_data_size);

//enum TreeFuncStatus TreeReadFromFile (FILE *file_with_tree, Tree *tree_for_fill);

//enum TreeFuncStatus TreeNodeRead (FILE *file_for_read_tree, TreeNode **tree_node_for_fill);

//enum TreeFuncStatus TreeNodeNilCheck (FILE *file_for_node_nil_check, char *buffer_for_node_check);

//enum TreeFuncStatus TreeNodeDataRead (FILE *file_for_read_node_data, TreeNode *tree_node_for_data_read,
//                                      char *buffer_for_read_node_data);

//enum TreeFuncStatus TreeOutputToFile (FILE *file_for_output_tree, const Tree *tree_for_output);

//enum TreeFuncStatus TreeNodeOutputToFile (FILE *file_for_output_node,
//                                          const TreeNode *tree_node_for_output);

//enum TreeFuncStatus TreeElementFind (const Tree *tree_for_element_find, const TreeElem_t tree_data_to_find,
//                                     Stack *stack_tree_path);

//enum TreeFuncStatus TreeNodeElementFind (const TreeNode *tree_node_for_element_find,
//                                         const TreeElem_t tree_node_data_to_find,
//                                         Stack *stack_tree_node_path);

//enum TreeFuncStatus TreeCompareData (const TreeNode *tree_node_for_cmp_data,
//                                     const TreeElem_t data_to_cmp);

enum TreeFuncStatus TreeCycledNodeSearch (const TreeNode *tree_node_for_cycle_search);

enum TreeFuncStatus TreeNodeFromPoisonSearch (const TreeNode *tree_node_for_poison_search);

enum TreeFuncStatus TreeNodeSwap (TreeNode *tree_node_for_swap, TreeNode *tree_node_new);

enum TreeFuncStatus TreeNodeClear (TreeNode *tree_node_for_destruct);

enum TreeFuncStatus TreeAllNodesDestruct (TreeNode **tree_node_for_destruct);

enum TreeFuncStatus TreeDtor (Tree *tree_for_destruct);

bool IsBracketInFileStr (FILE *file_to_check_str, const char bracket_type);

unsigned int TreeVerify (const Tree *tree_for_verify, const char *name_parent_func);

unsigned int TreeNodeVerify (const TreeNode *tree_node_for_verify);




#endif
