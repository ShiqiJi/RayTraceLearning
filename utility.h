#include <cmath>

double randomDouble()
{
    return rand() / (RAND_MAX + 1.0);
}

double randomDouble(double min, double max)
{
    return randomDouble() * (max -min) + min;
}

inline double limitValue(double value, double min, double max)
{
    if(value < min) return min;
    if(value > max) return max;
    return value;
}