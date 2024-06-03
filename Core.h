#include <math.h>

# define TOLERANCE 0.0000001

static bool isEqualD(double x, double y)
{
    return fabs(x - y) < TOLERANCE;
}