

#include "jwt.h"

#include <sstream>
#include "base64.h"


namespace jwt {


    const string Token::encode() const {

        stringstream stream;

        write_header(stream);
        stream << ".";
        write_body(stream);

        std::string out = m_signer->sign(stream.str());
        //auto o = base64_encode(reinterpret_cast<unsigned char *>(&*out.begin()), out.length());
        //base64uri_encode(o);

        stream << "." << out;
        return stream.str();
    }


    void Token::write_header(std::stringstream &stream) const
    {
        string out = "{\"typ\":\"JWT\",\"alg\":\"" + std::string(m_signer->name()) + "\"}";
        auto o = base64_encode(reinterpret_cast<unsigned char *>(&*out.begin()), out.length());
        base64uri_encode(o);
        stream << o;
    }

    void Token::write_body(std::stringstream &stream) const {
        string out("{}");
        if (!this->m_claims.empty()) {
            out = this->m_claims.dump();
            std::cout << "OUT " << out << std::endl;
        }


        auto o = base64_encode(reinterpret_cast<const unsigned char *>(&*out.begin()), out.length());
        base64uri_encode(o);
        stream << o;
    }


    std::string decode_segment(const std::string &payload, int start, int end) {
       auto bbody = payload.substr(start, end);
       base64uri_decode(bbody);
       return base64_decode(bbody);
    }

    std::unique_ptr<Token> decode(Strategy *s, const std::string &payload) {

        Token *token = new Token(s);

        auto len = payload.length();
        unsigned long i = 0;

        int hi = 0;

        std::string header, body;

        while (i < len) {
            if (payload[i++] == '.') {
                if (hi == 0) {
                    header = decode_segment(payload, hi, i-1);
                } else {
                    body = decode_segment(payload, hi, i-1);
                    break;
                }

                hi = i;
            }
        }

        auto ho = json::parse(header);
        auto cl = json::parse(body);

        if (!s->verify(payload)) {
            throw Exception("could not be verified");
        }

        token->m_claims = cl;

        return std::unique_ptr<Token>(token);
    }

}
