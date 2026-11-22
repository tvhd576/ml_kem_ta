
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

char *getenv(const char *name)
{
    /* No Linux process environment in this TA. */
    (void)name;
    return NULL;
}

static int digit_value(unsigned char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;

    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;

    return -1;
}

long strtol(const char *nptr,
            char **endptr,
            int base)
{
    const char *p = nptr;
    unsigned long value = 0;
    unsigned long limit;
    int negative = 0;
    int found = 0;
    int overflow = 0;
    int digit;

    if (endptr)
        *endptr = (char *)nptr;

    if (base != 0 && (base < 2 || base > 36)) {
        errno = EINVAL;
        return 0;
    }

    while (*p == ' ' || (*p >= '\t' && *p <= '\r'))
        p++;

    if (*p == '-' || *p == '+') {
        negative = (*p == '-');
        p++;
    }

    if ((base == 0 || base == 16) &&
        p[0] == '0' &&
        (p[1] == 'x' || p[1] == 'X') &&
        digit_value(p[2]) >= 0 &&
        digit_value(p[2]) < 16) {
        base = 16;
        p += 2;
    }

    if (base == 0)
        base = (*p == '0') ? 8 : 10;

    limit = negative
        ? (unsigned long)LONG_MAX + 1UL
        : (unsigned long)LONG_MAX;

    while ((digit = digit_value(*p)) >= 0 &&
           digit < base) {
        found = 1;

        if (value > (limit - (unsigned long)digit)
                    / (unsigned long)base) {
            overflow = 1;
        } else if (!overflow) {
            value = value * (unsigned long)base
                  + (unsigned long)digit;
        }

        p++;
    }

    if (!found)
        return 0;

    if (endptr)
        *endptr = (char *)p;

    if (overflow) {
        errno = ERANGE;
        return negative ? LONG_MIN : LONG_MAX;
    }

    if (negative) {
        if (value == (unsigned long)LONG_MAX + 1UL)
            return LONG_MIN;

        return -(long)value;
    }

    return (long)value;
}
