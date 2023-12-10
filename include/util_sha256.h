#ifndef _UTIL_SHA256_
#define _UTIL_SHA256_

#include <includes.h>



void compute_hmac_sha256(const char* key, const char* message, size_t message_len, unsigned char* hmac_digest);

#endif