#ifndef JWT_H
#define JWT_H

#include <exception>
#include <string>
//#include "claim.h"
#include "algo/algo.h"
//#include "algo/hmac.h"
#include "exception.h"

#include <iostream>

#include "../vendor/json/src/json.hpp"

using std::stringstream;
using std::string;
using json = nlohmann::json;


namespace jwt {

    typedef json Claim;

    class Token {
    public:
        Token(Strategy *s): m_signer(s) { }
        ~Token() {
            delete m_signer;
        }

        std::string encode();

        template<class T>
        void set_claim(const std::string &key, T claim) {
            m_claims[key] = claim;
        }

        template<class T>
        T get_claim(const std::string &key) {
            return m_claims[key];
        }

	private:
        Claim m_claims;
        //ClaimSet m_claims;
        Strategy *m_signer;

        void write_header(stringstream &stream);
        void write_body(stringstream &stream);

        friend std::unique_ptr<Token> decode(Strategy *s, const string &payload);
	};


    std::unique_ptr<Token> decode(Strategy *s, const string &payload);

	
}


#endif
