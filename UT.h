/*
 * UT.h
 *
 *  Created on: 15-Apr-2014
 *      Author: Systemantics
 */

#ifndef UT_H_
#define UT_H_

#include <stdint.h>

/*=================================================================
 *  Typedefs and Data Structures
 *=================================================================*/

typedef void (*UT_InitializeFunc)(void);  /**< Signature for suite initialization function. */
typedef void (*UT_CleanupFunc)(void);     /**< Signature for suite cleanup function. */
typedef void (*UT_TestFunc)(void);        /**< Signature for a testing function in a test case. */

int16_t UT_assertImplementation(int condition, char* fileName, int line,
                                        int numArgs, int arg0, int arg1);
/* Returns 1 if true, otherwise 0. Takes 2 arguments which are displayed
 * is assertion fails  */
#define UT_ASSERT2(cond, arg0, arg1) \
        UT_assertImplementation((cond), __FILE__, __LINE__, 2, arg0, arg1);

/* Returns 1 if true, otherwise 0. Takes 1 argument which is displayed
 * is assertion fails  */
#define UT_ASSERT1(cond, arg0) \
        UT_assertImplementation((cond), __FILE__, __LINE__, 1, arg0, 0);

/* Returns 1 if true, otherwise 0 */
#define UT_ASSERT0(cond) \
        UT_assertImplementation((cond), __FILE__, __LINE__, 0, 0, 0);

#define UT_ASSERT0FLOAT(op1, op2, tolerance) \
        UT_assertImplementation((op1 < op2 +  tolerance) && op1 > op2 - tolerance, __FILE__, __LINE__, 0, 0, 0);

/* Initialize the test harness */
void UT_initialize_registry();

void UT_add_suite(char *strName,
                  UT_InitializeFunc pInit,
                  UT_CleanupFunc pClean,
                  UT_TestFunc pTest);

void UT_cleanup_registry();

void UT_run_tests();

#endif /* UT_H_ */
