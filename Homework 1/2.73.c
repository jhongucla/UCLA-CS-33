/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y)
{
    int w = sizeof(x) << 3;
    int sum = x + y;
    int TMIN = 1 << (w-1);
    int TMAX = ~TMIN;
    int mask = 1 << (w-1);
    int x_sign = x & mask;
    int y_sign = y & mask;
    int sum_sign = sum & mask;
    int pos_overflow = ~x_sign & ~y_sign & sum_sign;
    int neg_overflow = x_sign & y_sign & !sum_sign;
    (pos_overflow) && (sum = TMAX);
    (neg_overflow) && (sum = TMIN);
    return sum;
}
