
#ifndef USER_TA_HEADER_DEFINES_H
#define USER_TA_HEADER_DEFINES_H

#include <mlkem_bench_ta.h>

/* Identify this Trusted Application */
#define TA_UUID TA_MLKEM_BENCH_UUID

/* TA configuration flags */
#define TA_FLAGS 0

/* Stack size: 4 KiB */
#define TA_STACK_SIZE (64 * 1024)

/* Heap size: 64 KiB */
#define TA_DATA_SIZE (4 * 1024 * 1024)

/* TA metadata */
#define TA_VERSION "0.1"

#define TA_DESCRIPTION "ML-KEM Benchmark Trusted Application"

#endif
