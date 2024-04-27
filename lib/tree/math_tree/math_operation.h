#ifndef MATH_OPERATION_H
#define MATH_OPERATION_H

const double EPS = 0.001;

/**
    Function that find maximum among two floating point numbers.
    @param [in] number_1 first number
    @param [in] number_2 second number
    @return maximum number
    @see Minimum()
*/
double Maximum (const double number_1, const double number_2);

/**
    Function that find minimum among two floating point numbers.
    @param [in] number_1 first number
    @param [in] number_2 second number
    @return minimum number
    @see Maximum()
*/
double Minimum (const double number_1, const double number_2);

/**
    Function that checks if floating point number is a zero.
    @param [in] number first number
    @return 1 if number is a zero, 0 if number is not a zero
*/
int IsZero (const double number);

/**
    Function that that checks if two floating point numbers are equal.
    @param [in] number_1 first number
    @param [in] number_2 second number
    @return 1 if numbers equal, 0 if numbers does not equal
    @see IsZero(), IsDoubleBigger()
*/
int IsDoublesEqual (const double number_1, const double number_2);

/**
    Function that checks if first floating point number is bigger than second floating point number.
    @param [in] number_1 first number
    @param [in] number_2 second number
    @return 1 if first number is bigger than second, 0 if not
    @see IsDoubleEqual()
*/

int IsDoubleBigger (const double number_1, const double number_2);

unsigned long long Factorial (const unsigned long long number);

#endif
