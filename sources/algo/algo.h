#ifndef JWT_ALGO_H
#define JWT_ALGO_H

#include <string>

namespace jwt {

class Strategy {
public:
    virtual ~Strategy() {}
    virtual const char *name() const = 0;
    virtual std::string sign(const std::string &payload) = 0;
    virtual bool verify(const std::string &) = 0;
};




}

#endif
