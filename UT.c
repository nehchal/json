/*
 * systcs_UT.c
 *
 *  Created on: 14-Apr-2014
 *      Author: Nehchal J. (nehchalj@gmail.com)
 */


#include "UT.h"
#include <stdint.h>

#include <xdc/runtime/System.h>

typedef struct{
  char*       pName;            /**< Suite name. */
  UT_TestFunc       pTestFunc;        /**< Pointer to the test runner in the suite. */
  UT_InitializeFunc pInitializeFunc;  /**< Pointer to the suite initialization function. */
  UT_CleanupFunc    pCleanupFunc;     /**< Pointer to the suite cleanup function. */
  int16_t hasFailed;
} UT_tSuite;

static struct {
  UT_tSuite suites[10];
  int16_t numSuites;
  int16_t currSuite;    // currentSuite being tested
  int16_t numPassed;
  int16_t numFailed;

  int16_t numAsserts;
  int16_t numAssertsPassed;
  int16_t numAssertsFailed;
} mod;

int16_t UT_assertImplementation(int cond, char* fileName, int line, int numArgs, int arg0, int arg1){

    mod.numAsserts++;

    if (!cond){
        System_printf("  Test: \"%s\" %d: Assert failed.", fileName, line);

        mod.suites[mod.currSuite].hasFailed = 1;

        mod.numAssertsFailed++;

        if (numArgs>=1)
            System_printf(" Arg0 = %d", arg0);
        if (numArgs>=2)
            System_printf(" Arg1 = %d", arg1);

        System_printf("\n");
        System_flush();
    }
    else
        mod.numAssertsPassed++;

    return cond;
}


/* Initialize the test harness */
void UT_initialize_registry(){
    mod.numSuites  = 0;
    mod.numAsserts = 0;
    mod.numPassed  = 0;
    mod.numFailed  = 0;
    mod.numAsserts = 0;
    mod.numAssertsPassed = 0;
    mod.numAssertsFailed = 0;

    return;
}

void UT_add_suite(char *strName,
                  UT_InitializeFunc pInit,
                  UT_CleanupFunc pClean,
                  UT_TestFunc pTest){

    mod.suites[mod.numSuites].pName           = strName;
    mod.suites[mod.numSuites].pInitializeFunc = pInit;
    mod.suites[mod.numSuites].pTestFunc       = pTest;
    mod.suites[mod.numSuites].pCleanupFunc    = pClean;
    mod.suites[mod.numSuites].hasFailed       = 0;
    mod.numSuites++;

    return;
}

void UT_cleanup_registry(){
    return;
}

void UT_run_tests(){

    int i;

    for (i=0; i < mod.numSuites; i++){
        System_printf("Suite: %s\n", mod.suites[i].pName);
        System_flush();

        mod.currSuite = i;

        mod.suites[i].pInitializeFunc();
        mod.suites[i].pTestFunc();
        mod.suites[i].pCleanupFunc();

        if(mod.suites[i].hasFailed){
            System_printf("  ...[Suite Failed]\n");
            mod.numFailed++;
        }
        else{
            System_printf("  ...[Suite Passed]\n");
            mod.numPassed++;
        }
        System_flush();

        System_printf("\n");
        System_flush();


    }


    System_printf("--Run Summary: Type      Total    Passed  Failed\n");
    System_flush();
    System_printf("               suites    %d        %d       %d\n",
                    mod.numSuites, mod.numPassed, mod.numFailed);
    System_flush();
    System_printf("               asserts   %d        %d       %d\n",
                    mod.numAsserts, mod.numAssertsPassed, mod.numAssertsFailed);
    System_flush();

    return;
}

