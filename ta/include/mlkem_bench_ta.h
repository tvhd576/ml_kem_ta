
#ifndef MLKEM_BENCH_TA_H
#define MLKEM_BENCH_TA_H

/*
 * Unique identifier of our ML-KEM Trusted Application.
 * Shared by Client Application and Trusted Application.
 */
#define TA_MLKEM_BENCH_UUID \
    { 0xb6f0ea85, 0xe408, 0x46d3, \
      { 0x89, 0x11, 0x9f, 0x09, \
        0xb5, 0x24, 0x93, 0x6e } }

/*
 * Commands supported by ML-KEM Benchmark TA.
 */
#define TA_MLKEM_CMD_PING    0
#define TA_MLKEM_CMD_KEYGEN  1
#define TA_MLKEM_CMD_ENCAP   2
#define TA_MLKEM_CMD_DECAP   3
#define TA_MLKEM_CMD_RUN 4

#endif /* MLKEM_BENCH_TA_H */
