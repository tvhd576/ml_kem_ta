#ifndef OPTEE_COMPAT_STRING_H
#define OPTEE_COMPAT_STRING_H

#include_next <string.h>

char *strcat(char *dest, const char *src);

size_t strspn(const char *s, const char *accept);

size_t strcspn(const char *s, const char *reject);

char *strpbrk(const char *s, const char *accept);

char *strerror(int errnum);

#endif
