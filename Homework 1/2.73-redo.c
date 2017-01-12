#include <stdbool.h>
/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y)
{
    int w = sizeof(x) << 3;
    int sum;
    int TMIN = 1 << (w-1);
    int TMAX = ~TMIN;
    int mask = 1 << (w-1);
    int x_sign = x & mask;
    int y_sign = y & mask;
    bool overflow = __builtin_add_overflow(x, y, &sum);
    (!x_sign) && (!y_sign) && (overflow) && (sum = TMAX);
    (x_sign) && (y_sign) && (overflow) && (sum = TMIN);
    return sum;
}
