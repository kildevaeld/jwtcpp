#ifndef JWT_HMAC_H
#define JWT_HMAC_H

#include "algo.h"
#include <string>
#include <sstream>
#include <memory>
#include <iostream>
#include <vector>
#include <cstring>
namespace jwt {

class Key {
public:
    Key(std::string key) {
        std::copy(key.begin(), key.end(), std::back_inserter(m_data));
    }

    Key(const char *key) {
        int len = std::strlen(key);
        int i = 0;
        while (i<len) {
            m_data.push_back(key[i++]);
        }
    }

    Key(unsigned char *key, size_t len) {
        int i = 0;
        while(i<len) {
            m_data.push_back(key[i++]);
        }
    }

    const unsigned char *data() const {
        return &m_data[0];
    }

    int length() {
        return m_data.size();
    }

private:
    std::vector<unsigned char> m_data;
};


enum Algorithm {
    sha256, sha384, sha512
};

class Hmac : public Strategy {

public:
    Hmac(Algorithm algo, Key key):algo(algo), key(key) {}

    // Strategy interface
public:
    const char *name() const  {
        switch (this->algo) {
        case sha256:
            return "HS256";
        case sha384:
            return "HS384";
        case sha512:
            return "HS512";
        default:
            return "None";
        }
    }

    // Strategy interface
public:
    std::string sign(const std::string &str);
    virtual bool verify(const std::string &payload);

private:
    Algorithm algo;
    Key key;


};






}


#endif
