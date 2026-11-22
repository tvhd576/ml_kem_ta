#include <stddef.h>
#include <errno.h>
#include <sys/time.h>
#include <tee_internal_api.h>

int optee_compat_errno = 0;

int gettimeofday(struct timeval *tv, void *tz)
{
    TEE_Time now;

    if (tv == NULL || tz != NULL) {
        errno = EINVAL;
        return -1;
    }

    TEE_GetREETime(&now);

    tv->tv_sec = (time_t)now.seconds;
    tv->tv_usec = (long)now.millis * 1000L;

    return 0;
}

time_t time(time_t *result)
{
    TEE_Time now;
    time_t seconds;

    TEE_GetREETime(&now);

    seconds = (time_t)now.seconds;

    if (result != NULL)
        *result = seconds;

    return seconds;
}

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    uint64_t ms;
    TEE_Result res;

    if (req == NULL || req->tv_sec < 0 ||
        req->tv_nsec < 0 || req->tv_nsec >= 1000000000L) {
        errno = EINVAL;
        return -1;
    }

    if ((uint64_t)req->tv_sec > 4294967294ULL / 1000ULL) {
        errno = EINVAL;
        return -1;
    }

    ms = (uint64_t)req->tv_sec * 1000ULL
       + ((uint64_t)req->tv_nsec + 999999ULL) / 1000000ULL;

    if (ms >= 4294967295ULL) {
        errno = EINVAL;
        return -1;
    }

    res = TEE_Wait((uint32_t)ms);

    if (res != TEE_SUCCESS) {
        errno = EINTR;
        return -1;
    }

    if (rem != NULL) {
        rem->tv_sec = 0;
        rem->tv_nsec = 0;
    }

    return 0;
}
