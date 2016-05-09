#include "object.h"


#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
#include <iostream>
#include <sstream>
#include "exception.h"

#include <cstdio>

using rapidjson::Document;
using rapidjson::Value;

//using rapidjson::StringBuffer;
//using rapidjson::PrettyWriter;
//using rapidjson::Writer;
namespace jwt {


bool Object::has(const char *key) {
    return this->m_map.count(key) > 0;
}

Any &Object::get(const char *key) {
    return m_map[key];
}


std::string Object::encode()  {
  std::stringstream stream;
  stream << "{";
  bool first = true;
  for (auto kv : m_map) {
    if (!first) stream << ",";
    stream << "\"" << kv.first << "\":";

    Any second = kv.second;

    if (second.is<string>()) {
      stream << "\"" << second.as<string>() << "\"";
    } else if (second.is<const char *>()) {
      stream << "\"" << second.as<const char*>() << "\"";
    } else if (second.is<bool>()) {
      stream << (second.as<bool>() ? "true" : "false");
    } else if (second.is<int>()) {
      stream << second.as<int>();
    } else if (second.is<uint>()) {
      stream << second.as<uint>();
    } else if (second.is<double>()) {
      stream << second.as<double>();
    } else if (second.is<Object>()) {
      auto str = second.as<Object>().encode();
      stream << str;
    } else {
        throw Exception("Wrong type");
    }

    first = false;
  }
  stream << "}";

  return stream.str();
}

Object Object::decode(const string &value)
{
    Document doc;
    doc.Parse(value.c_str());

    if (!doc.IsObject()) {
        throw new Exception("Root must be an object");
    }

    Object root;
    static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
    for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr) {
        switch (itr->value.GetType()) {
        case rapidjson::kNullType:
            break;
        case rapidjson::kNumberType:
            break;
        case rapidjson::kStringType:
            root.set(itr->name.GetString(), std::string(itr->value.GetString()));
            break;
        case rapidjson::kObjectType:
            std::cout << "whar " << itr->value.GetString() << std::endl;
            //root.set(itr->name.GetString(), Object::decode(itr->value.GetString()));
            break;
        //default:
          //  if (itr->value.IsBool()) {
          //      root.set(itr->name.GetString(), itr->value.Get<bool>());
          //  }
        }

    }

    return root;
}


}
