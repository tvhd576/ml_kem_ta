
#include <tee_internal_api.h>

#include <openssl/evp.h>
#include <openssl/crypto.h>

#include "mlkem_ops.h"

TEE_Result mlkem_run(uint32_t bits)
{
    const char *algorithm;
    size_t expected_ciphertext_len;

    EVP_PKEY_CTX *keygen_ctx = NULL;
    EVP_PKEY_CTX *encap_ctx = NULL;
    EVP_PKEY_CTX *decap_ctx = NULL;

    EVP_PKEY *key = NULL;

    /* Largest ciphertext: ML-KEM-1024 = 1568 bytes */
    unsigned char ciphertext[1568];

    /* Shared secret size for all ML-KEM variants = 32 bytes */
    unsigned char secret1[32];
    unsigned char secret2[32];

    size_t ciphertext_len = sizeof(ciphertext);
    size_t secret1_len = sizeof(secret1);
    size_t secret2_len = sizeof(secret2);

    TEE_Result result = TEE_ERROR_GENERIC;

    /* Select ML-KEM parameter set */
    switch (bits) {
    case 512:
        algorithm = "ML-KEM-512";
        expected_ciphertext_len = 768;
        break;

    case 768:
        algorithm = "ML-KEM-768";
        expected_ciphertext_len = 1088;
        break;

    case 1024:
        algorithm = "ML-KEM-1024";
        expected_ciphertext_len = 1568;
        break;

    default:
        return TEE_ERROR_BAD_PARAMETERS;
    }

    /* ========================================
     * 1. Key Generation
     * ======================================== */
    keygen_ctx = EVP_PKEY_CTX_new_from_name(
        NULL, algorithm, NULL
    );

    if (keygen_ctx == NULL)
        goto cleanup;

    if (EVP_PKEY_keygen_init(keygen_ctx) <= 0)
        goto cleanup;

    if (EVP_PKEY_keygen(keygen_ctx, &key) <= 0)
        goto cleanup;

    /* ========================================
     * 2. Encapsulation
     * ======================================== */
    encap_ctx = EVP_PKEY_CTX_new_from_pkey(
        NULL, key, NULL
    );

    if (encap_ctx == NULL)
        goto cleanup;

    if (EVP_PKEY_encapsulate_init(encap_ctx, NULL) <= 0)
        goto cleanup;

    if (EVP_PKEY_encapsulate(
            encap_ctx,
            ciphertext, &ciphertext_len,
            secret1, &secret1_len) <= 0)
        goto cleanup;

    /* ========================================
     * 3. Decapsulation
     * ======================================== */
    decap_ctx = EVP_PKEY_CTX_new_from_pkey(
        NULL, key, NULL
    );

    if (decap_ctx == NULL)
        goto cleanup;

    if (EVP_PKEY_decapsulate_init(decap_ctx, NULL) <= 0)
        goto cleanup;

    if (EVP_PKEY_decapsulate(
            decap_ctx,
            secret2, &secret2_len,
            ciphertext, ciphertext_len) <= 0)
        goto cleanup;

    /* ========================================
     * 4. Validate ciphertext length
     * ======================================== */
    if (ciphertext_len != expected_ciphertext_len)
        goto cleanup;

    /* ========================================
     * 5. Validate shared secret lengths
     * ======================================== */
    if (secret1_len != 32 || secret2_len != 32)
        goto cleanup;

    /* ========================================
     * 6. Compare shared secrets
     * ======================================== */
    if (CRYPTO_memcmp(secret1, secret2, 32) != 0)
        goto cleanup;

    /* All operations completed successfully */
    result = TEE_SUCCESS;

cleanup:
    /* Clear sensitive shared secrets */
    OPENSSL_cleanse(secret1, sizeof(secret1));
    OPENSSL_cleanse(secret2, sizeof(secret2));

    /* Release OpenSSL resources */
    EVP_PKEY_CTX_free(decap_ctx);
    EVP_PKEY_CTX_free(encap_ctx);
    EVP_PKEY_CTX_free(keygen_ctx);
    EVP_PKEY_free(key);

    return result;
}

