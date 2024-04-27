#ifndef DSL_COMMANDS_H
#define DSL_COMMANDS_H

#define cL                  (TreeNodeCopy (NULL, current_node -> left_branch, sizeof (MathNode)))

#define cR                  (TreeNodeCopy (NULL, current_node -> right_branch, sizeof (MathNode)))

#define cCUR                (TreeNodeCopy (NULL, current_node, sizeof (MathNode)))

#define ADD_(...)           (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_ADD, __VA_ARGS__))

#define SUB_(...)           (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_SUB, __VA_ARGS__))

#define MUL_(...)           (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_MUL, __VA_ARGS__))

#define DIV_(...)           (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_DIV, __VA_ARGS__))

#define POW_(...)           (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_POW, __VA_ARGS__))

#define SIN_(...)           (CreateMathTreeNode (UNARY_OPERATOR, OPERATOR_SIN, __VA_ARGS__, NULL))

#define COS_(...)           (CreateMathTreeNode (UNARY_OPERATOR, OPERATOR_COS, __VA_ARGS__, NULL))

#define SQRT_(...)          (CreateMathTreeNode (UNARY_OPERATOR, OPERATOR_SQRT, __VA_ARGS__, NULL))

#define LN_(...)            (CreateMathTreeNode (UNARY_OPERATOR, OPERATOR_LN, __VA_ARGS__, NULL))

#define OPEN_PARENTHESIS_   (CreateMathTreeNode (UNARY_OPERATOR, OPERATOR_OPEN_PARENTHESIS, NULL, NULL))

#define CLOSE_PARENTHESIS_  (CreateMathTreeNode (UNARY_OPERATOR, OPERATOR_CLOSE_PARENTHESIS, NULL, NULL))

#define NUM_(...)           (CreateMathTreeNode (NUMBER, __VA_ARGS__, NULL, NULL))

#define VAR_(...)           (CreateMathTreeNode (VARIABLE, __VA_ARGS__, NULL, NULL))

#define EQUAL_(...)         (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_EQUAL, __VA_ARGS__))

#define NOT_EQUAL_(...)     (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_NOT_EQUAL, __VA_ARGS__))

#define GREATER_(...)       (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_GREATER, __VA_ARGS__))

#define LESS_(...)          (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_LESS, __VA_ARGS__))

#define GREATER_EQ_(...)    (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_GREATER_EQ, __VA_ARGS__))

#define LESS_EQ_(...)       (CreateMathTreeNode (BINARY_OPERATOR, OPERATOR_LESS_EQ, __VA_ARGS__))

#define ASSIGN_             (CreateLangTreeNode (ASSIGN, NULL, NULL))

#define END_LINE_(...)      (CreateLangTreeNode (END_LINE, __VA_ARGS__, NULL))

#define INIT_(...)          (CreateLangTreeNode (INIT, __VA_ARGS__))

#define TYPE_INT_           (CreateLangTreeNode (TYPE_INT, NULL, NULL))

#define PRINT_              (CreateLangTreeNode (PRINT, NULL, NULL))

#define IF_(...)            (CreateLangTreeNode (IF, __VA_ARGS__, NULL))

#define WHILE_(...)         (CreateLangTreeNode (WHILE, __VA_ARGS__, NULL))

#define READ_               (CreateLangTreeNode (READ, NULL, NULL))

#define FUNC_(...)          (CreateLangTreeNode (FUNC, __VA_ARGS__, NULL))

#define FUNC_CALL_(...)     (CreateLangTreeNode (FUNC_CALL, __VA_ARGS__, NULL))

#define FUNC_RET_(...)      (CreateLangTreeNode (FUNC_RET, __VA_ARGS__, NULL))

#define NEW_FUNC_(...)      (CreateLangTreeNode (NEW_FUNC, NULL, __VA_ARGS__))

#define COMMA_(...)         (CreateLangTreeNode (COMMA,__VA_ARGS__))

#define AND_(...)           (CreateLangTreeNode (AND, __VA_ARGS__))

#define OR_(...)            (CreateLangTreeNode (OR, __VA_ARGS__))

#define END_                (CreateMathTreeNode (END, 0, NULL, NULL))

#endif
