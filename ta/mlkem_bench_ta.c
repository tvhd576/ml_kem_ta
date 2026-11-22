
#include <tee_internal_api.h>

#include "mlkem_bench_ta.h"
#include "mlkem_ops.h"

TEE_Result TA_CreateEntryPoint(void)
{
    return TEE_SUCCESS;
}

void TA_DestroyEntryPoint(void)
{
}

TEE_Result TA_OpenSessionEntryPoint(
    uint32_t param_types,
    TEE_Param params[4],
    void **sess_ctx)
{
    uint32_t expected = TEE_PARAM_TYPES(
        TEE_PARAM_TYPE_NONE,
        TEE_PARAM_TYPE_NONE,
        TEE_PARAM_TYPE_NONE,
        TEE_PARAM_TYPE_NONE
    );

    (void)params;

    if (param_types != expected)
        return TEE_ERROR_BAD_PARAMETERS;

    *sess_ctx = NULL;
    return TEE_SUCCESS;
}

void TA_CloseSessionEntryPoint(void *sess_ctx)
{
    (void)sess_ctx;
}

TEE_Result TA_InvokeCommandEntryPoint(
    void *sess_ctx,
    uint32_t cmd_id,
    uint32_t param_types,
    TEE_Param params[4])
{
    (void)sess_ctx;

    switch (cmd_id) {

    case TA_MLKEM_CMD_PING:
        if (param_types != TEE_PARAM_TYPES(
                TEE_PARAM_TYPE_VALUE_INOUT,
                TEE_PARAM_TYPE_NONE,
                TEE_PARAM_TYPE_NONE,
                TEE_PARAM_TYPE_NONE))
            return TEE_ERROR_BAD_PARAMETERS;

        params[0].value.a += 1;
        return TEE_SUCCESS;

    case TA_MLKEM_CMD_RUN:
        if (param_types != TEE_PARAM_TYPES(
                TEE_PARAM_TYPE_VALUE_INPUT,
                TEE_PARAM_TYPE_NONE,
                TEE_PARAM_TYPE_NONE,
                TEE_PARAM_TYPE_NONE))
            return TEE_ERROR_BAD_PARAMETERS;

        /* 768 = ML-KEM-768; 1024 = ML-KEM-1024 */
        return mlkem_run(params[0].value.a);

    default:
        return TEE_ERROR_NOT_SUPPORTED;
    }
}

