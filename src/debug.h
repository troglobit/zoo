/* Defines conditional function calls
 *
 * Usage:  The statement
 *
 *    debug((printf("y = %d\n", y)))
 *
 * may be placed anywhere where two or more statements could be used.
 * It will print the value of y at that point.
 *
 * Conditional compilation:
 *
 *    if DEBUG is defined
 *       define the macro debug(X) to execute statement X
 *    else
 *       define the macro debug(X) to be null
 *    endif
 *
 * The contents of this file are hereby released to the public domain.
 *
 *                              -- Rahul Dhesi 1986/11/14
 */

#ifdef DEBUG
#define  debug(x)    x;
#else
#define  debug(x)
#endif

