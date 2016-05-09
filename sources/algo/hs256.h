#ifndef JWT_HS256_H
#define JWT_HS256_H

#include "algo.h"

namespace jwt {

    /*class  HS256 : public JWTHmac {
    public:
        HS256(): JWTHmac(sha256) {}

    };*/

    class HS256: public Strategy {


        // Strategy interface
    public:
        virtual const std::__cxx11::string &decode(const char *payload, const char *key) {
            return std::string("");
        }

        virtual  std::__cxx11::string encode(const char *str, const char *key) {
            return std::string("");
        }
    };

}

#endif
