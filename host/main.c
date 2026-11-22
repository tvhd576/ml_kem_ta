
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <tee_client_api.h>
#include <mlkem_bench_ta.h>

int main(void)
{
    TEEC_Context ctx;
    TEEC_Session sess;
    TEEC_Operation op;
    TEEC_UUID uuid = TA_MLKEM_BENCH_UUID;

    TEEC_Result res;
    uint32_t err_origin = 0;
    uint32_t algorithms[] = {512, 768, 1024};
    int status = 1;

    /* Connect to OP-TEE */
    res = TEEC_InitializeContext(NULL, &ctx);

    if (res != TEEC_SUCCESS) {
        printf("InitializeContext failed: 0x%x\n", res);
        return 1;
    }

    /* Open our ML-KEM Trusted Application */
    res = TEEC_OpenSession(
        &ctx,
        &sess,
        &uuid,
        TEEC_LOGIN_PUBLIC,
        NULL,
        NULL,
        &err_origin
    );

    if (res != TEEC_SUCCESS) {
        printf("OpenSession failed: 0x%x\n", res);
        goto cleanup_context;
    }

    /* Run ML-KEM 512 and ML-KEM-768 and ML-KEM-1024 */
    for (int i = 0; i < 3; i++) {
        uint32_t bits = algorithms[i];

        memset(&op, 0, sizeof(op));

        op.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE
        );

        op.params[0].value.a = bits;

        printf("\n=== ML-KEM-%u ===\n", bits);
        printf("Running KeyGen -> Encap -> Decap...\n");

        res = TEEC_InvokeCommand(
            &sess,
            TA_MLKEM_CMD_RUN,
            &op,
            &err_origin
        );

        if (res != TEEC_SUCCESS) {
            printf("ML-KEM-%u: FAIL\n", bits);
            printf("TEE error: 0x%x\n", res);
            printf("Error origin: 0x%x\n", err_origin);
            goto cleanup_session;
        }

        printf("ML-KEM-%u: PASS\n", bits);
        printf("Shared secrets matched inside TA.\n");
    }

    printf("\nAll ML-KEM operations completed successfully.\n");
    status = 0;

cleanup_session:
    TEEC_CloseSession(&sess);

cleanup_context:
    TEEC_FinalizeContext(&ctx);

    return status;
}

