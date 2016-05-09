

#include "jwt.h"

#include <sstream>
#include "base64.h"

using std::stringstream;

namespace jwt {


    string Token::encode() {

        stringstream stream;

        write_header(stream);
        stream << ".";
        write_body(stream);

        std::string out = m_signer->sign(stream.str().c_str());
        //auto o = base64_encode(reinterpret_cast<unsigned char *>(&*out.begin()), out.length());
        //base64uri_encode(o);

        stream << "." << out;
        return stream.str();
    }


    void Token::write_header(std::stringstream &stream)
    {
        string out = "{\"typ\":\"JWT\",\"alg\":\"" + std::string(m_signer->name()) + "\"}";
        auto o = base64_encode(reinterpret_cast<unsigned char *>(&*out.begin()), out.length());
        base64uri_encode(o);
        stream << o;
    }

    void Token::write_body(std::stringstream &stream) {
        string out = this->claims()->encode();
        auto o = base64_encode(reinterpret_cast<unsigned char *>(&*out.begin()), out.length());
        base64uri_encode(o);
        stream << o;
    }


    std::string decode_segment(const std::string &payload, int start, int end) {
        auto bbody = payload.substr(start, end);
        base64uri_decode(bbody);
       return base64_decode(bbody);
    }

    Token &decode(Strategy *s, const std::string &payload) {

        auto len = payload.length();
        int i = 0;

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

        auto ho = Object::decode(header);
        auto cl = Object::decode(body);
        //std::cout << ho.encode() << std::endl;
        //std::cout << cl.encode() << std::endl;
        //std::cout << ho.get("alg").as<string>()<< "\n" << body << std::endl;
        //std::cout << payload.substr(i, len) << std::endl;
        std::cout << s->verify(payload) << std::endl;
    }

}
