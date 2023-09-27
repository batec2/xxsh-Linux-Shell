/* Helper functions to simplify testing */

#ifndef TESTING
#define TESTING

#include <stdio.h>
#include <stdlib.h>

/* Prints out success message.
 * @param desc description of test.
 */
void PASS(char *desc);

/* Prints out failure message.
 * @param desc description of test.
 */
void FAIL(char *desc);

/* Testing helper function.
 * @param result contains the result of the test: 1 is pass, 0 is fail.
 * @param desc of test being ran
 * TODO: Rewrite it to take a function to execute so it can print the
 * TESTING:.. message before the function runs.
 */
void test(int result, char *desc);

#endif /* TESTING */
