
#include <string.h>
#include <errno.h>

char *strcat(char *dest, const char *src)
{
    char *p = dest + strlen(dest);

    while ((*p++ = *src++) != '\0')
        ;

    return dest;
}

size_t strspn(const char *s, const char *accept)
{
    size_t n = 0;

    while (s[n] && strchr(accept, s[n]))
        n++;

    return n;
}

size_t strcspn(const char *s, const char *reject)
{
    size_t n = 0;

    while (s[n] && !strchr(reject, s[n]))
        n++;

    return n;
}

char *strpbrk(const char *s, const char *accept)
{
    while (*s) {
        if (strchr(accept, *s))
            return (char *)s;

        s++;
    }

    return NULL;
}

char *strerror(int errnum)
{
    static char success[] = "Success";
    static char invalid[] = "Invalid argument";
    static char memory[] = "Out of memory";
    static char io[] = "Input/output error";
    static char range[] = "Result out of range";
    static char unknown[] = "Unknown error";

    switch (errnum) {
    case 0:      return success;
    case EINVAL: return invalid;
    case ENOMEM: return memory;
    case EIO:    return io;
    case ERANGE: return range;
    default:     return unknown;
    }
}
