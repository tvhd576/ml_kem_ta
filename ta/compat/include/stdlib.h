#ifndef OPTEE_COMPAT_STDLIB_H
#define OPTEE_COMPAT_STDLIB_H

#include_next <stdlib.h>

char *getenv(const char *name);

long strtol(const char *nptr,
            char **endptr,
            int base);

#endif
