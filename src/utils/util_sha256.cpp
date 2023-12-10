#include "util_sha256.h"

// Calculating HMAC SHA-256 hash
void compute_hmac_sha256(const char* key, const char* message, size_t message_len, unsigned char* hmac_digest)
{
    const size_t key_len = strlen(key);

    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
    mbedtls_md_hmac_starts(&ctx, reinterpret_cast<const unsigned char*>(key), key_len);
    mbedtls_md_hmac_update(&ctx, reinterpret_cast<const unsigned char*>(message), message_len);
    mbedtls_md_hmac_finish(&ctx, hmac_digest);
    mbedtls_md_free(&ctx);
}

