#ifndef JWT_H
#define JWT_H

#include <exception>
#include <string>
#include "claim.h"
#include "algo/algo.h"
//#include "algo/hmac.h"
#include "exception.h"

#include <iostream>

namespace jwt {


    class Token {
    public:
        Token(Strategy *s): m_signer(s) { }
        ~Token() { delete m_signer; }

        std::string encode();

        ClaimSet *claims()  {
            return &m_claims;
        }

	private:
		ClaimSet m_claims;
        Strategy *m_signer;

        void write_header(stringstream &stream);
        void write_body(stringstream &stream);

	};


    Token &decode(Strategy *s, const string &payload);

	
}


#endif
