#ifndef JWT_ARRAY_H
#define JWT_ARRAY_H

#include <vector>

namespace jwt {


class Array {

    void push(const std::string &);



private:
    std::vector<Any> m_array;

};



}


#endif
