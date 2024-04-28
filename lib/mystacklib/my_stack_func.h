#ifndef MY_STACK_FUNC_H
#define MY_STACK_FUNC_H

#include <stdio.h>
#include <math.h>

#include "extern_for_stack.h"
#include "my_stack_func_additional.h"
#include "hash_func.h"

/// Macros that prints to log file.
#define LOG_PRINT_STACK(LOG_FILE_STACK, ...)  do {                                      \
                                                  fprintf(LOG_FILE_STACK, __VA_ARGS__); \
                                                  fflush (LOG_FILE_STACK);              \
                                                                                        \
                                              } while (0)

/// Macros that outputs name of variable.
#define NAME_OF_VAR(x)     #x

/// Macros that run StackDump() function.
#define STACK_DUMP(stk)    StackDump (stk, __FILE__, __func__, __LINE__, NAME_OF_VAR (stk))

/// Macros that verify the stack.
#define STACK_VERIFY(stk)  do {                          \
                               if (StackOk (stk) != 0) { \
                                   STACK_DUMP (stk);     \
                                   return FAIL;          \
                               }                         \
                           } while (0)

/// Checks whether canary protection is on or not.
#if CANARY_PROTECTION
    #define CANARY_ON(...) __VA_ARGS__
#else
    #define CANARY_ON(...)
#endif

/// Checks whether hash protection is on or not.
#if HASH_PROTECTION
    #define HASH_ON(...) __VA_ARGS__
#else
    #define HASH_ON(...)
#endif

/// Checks whether debugging is on or not.
#if DEBUG
    #define ON_DEBUG(...) __VA_ARGS__
#else
    #define ON_DEBUG(...)
#endif

/// Constant for canaries in stack.
const unsigned long long STACK_CANARY = 0xFEE1DEAD;

//const unsigned long long DEFAULT_STACK_CAPACITY = 1;

/// Max possible canary size in bytes.
const int MAX_CANARY_SIZE_BYTES = 8;

/// How many times capacity grows in StackRecalloc().
const int INCREASE_AMOUNT = 2;

/// How many times capacity is decreasing in StackRecalloc().
const int HOW_MUCH_STACK_DECREASES = 4;

/// How many times stack size should be lower than stack capacity to decrease the stack capacity.
const int DECREASE_AMOUNT = 2;

/// Poison number to data elements in stack.
const Elem_t POISON_NUM = NAN;

/// Struct that contains all info about stack.
struct Stack {

    Canary_t left_canary;

    Elem_t *data;
    int32_t capacity;
    int32_t stack_size;

    uint32_t stack_hash;
    uint32_t stack_data_hash;

    Canary_t right_canary;
};

/// Number of all stack errors.
const int STACK_ERRORS_AMOUNT = 6;

/// Enum that contains all stack errors.
enum StackErrors {

    STACK_PTR_NULL       = (1 << 0),   ///< Error describes null pointer to stack.
    WRONG_HASH           = (1 << 1),   ///< Error describes wrong stack hash or wrong hash of elements in data
    STACK_CANARY_DAMAGED = (1 << 2),
    DATA_PTR_NULL        = (1 << 3),   ///< Error describes null pointer to data.
    NEGATIVE_SIZE        = (1 << 4),   ///< Error describes negative stack size.
    NEGATIVE_CAPACITY    = (1 << 5),   ///< Error describes negative stack capacity.
};

/// Enum that contains stack function statuses.
enum StackFuncStatus {

    OK,                              ///< If function was run successfully.
    FAIL,                            ///< If error happened while function was running.
    NOTHING_HAPPENED                 /**< If stack capacity wasn't changed in StackRecalloc().
                                          Data wasn't changed in stack. Stack wasn't changed.
                                          Nothing wasn't changed at all. No function was called.
                                          No instruction was executed. The Sun wasn't moved in the sky.
                                          Nobody was moved or even breathed, no spirit was going
                                          under empty Earth. The God was not even created or started
                                          the Creature of the Universe. And was not the Light,
                                          and was not the Dark: was not the Day One. NOTHING HAPPENED.
                                          Special status for StackRecalloc(). */
};

/**
    Function that constructs the stack.
    @param [in, out] stk stack.
    @param [in] stack_capacity capacity of stack.
    @return \p OK if was done successfully, \p FAIL if error happened.
*/
enum StackFuncStatus StackCtor (Stack *stk, int32_t stack_capacity);

/**
    Function that destructs the stack.
    @param [in, out] stk stack.
    @return \p OK if was done successfully, \p FAIL if error happened.
*/
enum StackFuncStatus StackDtor (Stack *stk);

/**
    Function that constructs the data in stack.
    @param [in, out] stk stack.
    @return \p OK if was done successfully, \p FAIL if error happened.
*/
enum StackFuncStatus StackDataCtor (Stack *stk);

/**
    Function that puts poison number to each element in the data in stack.
    @param [in, out] stk stack.
    @return \p OK if was done successfully, \p FAIL if error happened.
*/
enum StackFuncStatus StackDataReset (Stack *stk);

/**
    Function that destructs the data in stack.
    @param [in, out] stk stack.
    @return \p OK if was done successfully, \p FAIL if error happened.
*/
enum StackFuncStatus StackDataDtor (Stack *stk);

/**
    Function that pushes the element to data.
    @param [in, out] stk stack.
    @param [in] value element that has to be pushed.
    @return \p OK if was done successfully, \p FAIL if error happened.
*/
enum StackFuncStatus StackPush (Stack *stk, Elem_t value);

/**
    Function that pops the element from data.
    @param [in, out] stk stack.
    @param [in, out] ret_value pointer to element that has to be popped.
    @return \p OK if was done successfully, \p FAIL if error happened.
*/
Elem_t StackPop (Stack *stk);

/**
    Function that changes stack capacity depending on stack size.
    @param [in, out] stk stack.
    @return \p OK if was done successfully, \p FAIL if error happened,
            \p NOTHING_HAPPENED if stack capacity wasn't changed.
*/
enum StackFuncStatus StackRecalloc (Stack *stk);

/**
    Function that verify the stack.
    @param [in, out] stk stack.
    @return 0 if there's no errors, any other number if there's any errors.
*/
unsigned int StackOk (Stack *stk);

/**
    Function that prints stack dump to log file.
    @param [in, out] stk stack.
    @return \p OK if was done successfully, \p FAIL if error happened.
*/
enum StackFuncStatus StackDump (Stack *stk_for_dump, const char *file,
                            const char *func_called, const int line_called,
                            const char *stack_name);

/**
    Function that generates hash of stack.
    @param [in, out] stk stack.
    @return \p OK if was done successfully, \p FAIL if error happened.
*/
enum StackFuncStatus StackHashGen (Stack *stk_for_hash);

/**
    Function that generates hash of elements in data in stack.
    @param [in, out] stk stack.
    @return \p OK if was done successfully, \p FAIL if error happened.
*/
enum StackFuncStatus StackDataHashGen (Stack *stk_for_hash);

/**
    Function that prints stack errors to log file.
    @param [in, out] errnum errors caught by STACK_DUMP().
    @return \p OK if was done successfully.
*/
enum StackFuncStatus LogPrintStackError (unsigned int errnum);


#endif
