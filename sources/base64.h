#ifndef JWT_BASE64_H
#define JWT_BASE64_H
#include <string>

namespace jwt {



std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

void base64uri_encode(std::string &str);
void base64uri_decode(std::string &str);

}


#endif
