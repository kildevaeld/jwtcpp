#ifndef JWT_BASE64_H
#define JWT_BASE64_H
#include <string>

namespace jwt {



std::string base64_encode(const unsigned char * , unsigned int len);
std::string base64_decode(const std::string & s);

void base64uri_encode(std::string &str);
void base64uri_decode(std::string &str);

}


#endif
