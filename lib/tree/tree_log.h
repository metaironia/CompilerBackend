#ifndef TREE_LOG_H
#define TREE_LOG_H

#include "tree_func.h"
#include "math_tree/math_tree_func.h"

#define TREE_DOT_FILE_NAME             "tree_dot_dump.dot"

#define NODE_START_SYMBOL              "A"

#define LOG_PRINT_TREE_ERROR(error)    LogPrintTreeError (error)

#define LOG_PRINT(LOG_FILE, ...)       do {                                \
                                           fprintf(LOG_FILE, __VA_ARGS__); \
                                           fflush (LOG_FILE);              \
                                       } while (0)

#define TREE_ERROR_SET_AND_PRINT(tree_errors, current_error)                       \
                                       {                                           \
                                           tree_errors |= current_error;           \
                                           LOG_PRINT_TREE_ERROR (#current_error);  \
                                       }

const int MAX_IMAGE_NAME_LENGTH = 64;

const int MAX_COMMAND_LENGTH    = 64;

FILE *CreateLogFile (const char *log_file_name);

void CloseLogFile (void);

enum TreeFuncStatus LogPrintTreeError (const char *error_text);

enum TreeFuncStatus MathTreeGraphDump (const Tree *tree_for_graph_dump, const NameTable *name_table);

enum TreeFuncStatus TreeImageFolderCreate (void);

enum TreeFuncStatus TreeDotFileBegin (FILE *tree_dot_file_begin);

enum TreeFuncStatus TreeDotFileEnd (FILE *tree_dot_file_end);

enum TreeFuncStatus TreeDotFileCreateElements (FILE *tree_dot_file_gen_elems,
                                               const TreeNode *tree_node_for_gen_elems,
                                               const NameTable *name_table);

enum TreeFuncStatus NodeTypePrint (FILE *tree_dot_file, const TreeNode *current_node,
                                   const NameTable *name_table);

enum TreeFuncStatus TreeDotFileDrawArrows (FILE *tree_dot_file_draw,
                                           const TreeNode *tree_node_for_draw_arrows);

enum TreeFuncStatus TreeDotFileSetColorElement (FILE *tree_dot_file_elem_for_set_color,
                                                const TreeNode *tree_node_for_set_color);

enum TreeFuncStatus TreeImageCreate (FILE *tree_dot_file);

const char *ImageNameCreate (void);

const char *CommandToCreateImageCreate (const char *image_name);

#endif
