#ifndef MACRO_FUNCTION_OVERLOAD_H

#define MACRO_FUNCTION_OVERLOAD_H

#include <stdio.h>

#define TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_ZERO(itv) printf("")
#define TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_ONE_INT(x0, itv) printf("%d", (x0))
#define TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_TWO_INT(x0, x1, itv) printf("%d"itv"%d", (x0), (x1))
#define TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_THREE_INT(x0, x1, x2, itv) printf("%d"itv"%d"itv"%d", (x0), (x1), (x2))
#define TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_FOUR_INT(x0, x1, x2, x3, itv) printf("%d"itv"%d"itv"%d"itv"%d", (x0), (x1), (x2), (x3))

#define TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_INT_CHANGER(p0, p1, p2, p3, p4, p5, ...) p5

#define TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_INT(...)\
TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_INT_CHANGER\
(__VA_ARGS__,\
TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_FOUR_INT, \
TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_THREE_INT, \
TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_TWO_INT, \
TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_ONE_INT, \
TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_ZERO, ...) (__VA_ARGS__)

#define PRINT_DEMO(...) __VA_ARGS__

#endif // !MACRO_FUNCTION_OVERLOAD_H
