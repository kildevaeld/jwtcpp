#ifndef JWT_EXCEPTION_H
#define JWT_EXCEPTION_H

namespace jwt {
class Exception : public std::exception {
public:
    Exception(const char *what): m_what(what) {}
    virtual const char* what() const throw()
      {
        return m_what;
      }
private:

    const char *m_what;

};


}

#endif
