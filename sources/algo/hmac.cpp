
#include "hmac.h"
#include "../exception.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "../base64.h"

#include <openssl/hmac.h>

#include <sstream>

namespace jwt {



std::string Hmac::sign(const char *str) {
    unsigned char res[key.length()];
    unsigned int res_len;

    const EVP_MD *alg;
    switch (this->algo) {
    case sha256:
        alg = EVP_sha256();
        break;
    case sha384:
        alg = EVP_sha384();
        break;
    case sha512:
        alg = EVP_sha512();
    default:
        throw Exception("none");
    }

    HMAC(alg, key.data(), key.length(),
         (const unsigned char *)str, strlen(str), res, &res_len);

    std::string out = base64_encode(res, res_len);
    base64uri_encode(out);

    return std::move(out);
}

bool Hmac::verify(const std::string &payload) {

    int len = payload.length();
    int i = 0, index = 0;

    while (i < len) {
        if (payload[i++] == '.') {
            if (index == 0) {
                index = 1;
            } else {
                index = i;
                break;
            }
        }
    }

    auto pp = payload.substr(0, i-1);
    return this->sign(pp.c_str()) == payload.substr(i);
}


}
