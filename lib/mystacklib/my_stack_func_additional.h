#ifndef MY_STACK_FUNC_ADDITIONAL_H
#define MY_STACK_FUNC_ADDITIONAL_H

/// Status of hash protection (0 - off, 1 - on)
#define HASH_PROTECTION 0

/// Status of canary protection (0 - off, 1 - on)
#define CANARY_PROTECTION 0

/// Status of debug (0 - off, 1 - on)
#define DEBUG 1

/// Printing format of element of data in stack.
#define EL_FORMAT "%lf"

/// Printing format of canaries in stack.
#define CAN_FORMAT "%I64X"

/// Type definition of element of data in stack.
typedef double Elem_t;

/// Type definition of canaries in stack.
typedef unsigned long long Canary_t;

/// Function exists to close log file.
void StackLogFileClose (void);

/// Exists to open log file.
FILE *StackLogFileOpen (const char *file);

#endif
