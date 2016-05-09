#ifndef JWT_OBJECT_H
#define JWT_OBJECT_H
#include <map>
#include <string>
#include <type_traits>
#include "any.h"

#define REQUIRES(...) typename std::enable_if<(__VA_ARGS__), int>::type = 0

namespace jwt {

class Object;

template<class T>
struct is_incrementable
        : std::integral_constant<bool, (
        std::is_same<T, uint>() ||
        std::is_same<T, int>() ||
        std::is_same<T, bool>() ||
        std::is_same<T, double>() ||
        std::is_same<T, Object>() ||
        std::is_same<T, std::string >())>
{};


class Object {


public:
    void set(const char *key, const char *value) {
        m_map[key] = value;
    }

    template<class T, REQUIRES(is_incrementable<T>())>
    void set(const char *key, const T& value) {
        m_map[key] = value;
    }

    template<class T, REQUIRES(is_incrementable<T>())>
    void set(const char *key, T& value) {
        m_map[key] = value;
    }


    bool has(const char *key);

    Any &get(const char *key);

    template<class T>
    bool is(const char *key) {
        if (!has(key)) return false;
        return m_map[key].is<T>();
    }


    string encode();

    static Object decode(const std::string &value);




protected:
    std::map<const char *, Any> m_map;

};

}

#endif
