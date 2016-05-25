
#include "hmac.h"
#include "../exception.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "../base64.h"

#include <openssl/hmac.h>

#include <sstream>

namespace jwt {



std::string Hmac::sign(const std::string &str) {
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

    auto ret = HMAC(alg, key.data(), key.length(),
         reinterpret_cast<const unsigned char *>(str.data()), str.length(), res, &res_len);

    std::string out = base64_encode(ret, res_len);
    base64uri_encode(out);

    return out;
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

    return this->sign(payload.substr(0, i-1)) == payload.substr(i);
}


}
