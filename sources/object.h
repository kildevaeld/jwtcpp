#ifndef JWT_OBJECT_H
#define JWT_OBJECT_H
#include <map>
#include <string>
#include <type_traits>
#include "any.h"
#include <memory>
#define REQUIRES(...) typename std::enable_if<(__VA_ARGS__), int>::type = 0

namespace jwt {

class Object;

template<class T>
struct is_incrementable
        : std::integral_constant<bool, (
        std::is_same<T, unsigned int>() ||
        std::is_same<T, int>() ||
        std::is_same<T, bool>() ||
        std::is_same<T, double>() ||
        std::is_same<T, Object>() ||
        std::is_same<T, std::string >())>
{};


class Object {


public:
    //Object () {}

    void set(const std::string &key, const char *value) {
        m_map[key] = value;
    }

    template<class T, REQUIRES(is_incrementable<T>())>
    void set(const std::string &key, const T& value) {
        m_map[key] = value;
    }

    template<class T, REQUIRES(is_incrementable<T>())>
    void set(const std::string &key, T& value) {
        m_map[key] = value;
    }


    bool has(const std::string &key);

    Any &get(const std::string &key);

    template<class T>
    bool is(const std::string &key) {
        if (!has(key)) return false;
        return m_map[key].is<T>();
    }


    string encode();

    static std::unique_ptr<Object> decode(const std::string &value);




protected:
    std::map<std::string, Any> m_map;

};

}

#endif
