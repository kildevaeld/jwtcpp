#include "object.h"


//#include "rapidjson/document.h"
//#include "rapidjson/rapidjson.h"
#include "json.hpp"
#include <iostream>
#include <sstream>
#include "exception.h"

#include <cstdio>

//using rapidjson::Document;
//using rapidjson::Value;

//using rapidjson::StringBuffer;
//using rapidjson::PrettyWriter;
//using rapidjson::Writer;
using namespace nlohmann;
 
namespace jwt {


bool Object::has(const std::string &key) {
    return this->m_map.count(key) > 0;
}

Any &Object::get(const std::string &key) {
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
    } else if (second.is<unsigned int>()) {
      stream << second.as<unsigned int>();
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

std::unique_ptr<Object> Object::decode(const string &value)
{
    auto j = json::parse(value);
    auto root = new Object();

    for (json::iterator it = j.begin() ; it != j.end(); it++) {
      auto value = it.value();
      if (value.is_string()) {
        //std::cout << it.key() << std::endl;
        //root[it.key()] = value.get<std::string>();
        //root->set(it.key(), value.get<std::string>());
      } /*else if (value.is_number_float()) {
          root->set(it.key(), value.get<double>());
      } else if (value.is_number_unsigned()) {
          root->set(it.key(), value.get<unsigned int>());
      } else if (value.is_number_integer()) {
          root->set(it.key(), value.get<int>());
      } else if (value.is_boolean()) {
          root->set(it.key(), value.get<bool>());
      }*/



    }
    /*Document doc;
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

    }*/

    return std::unique_ptr<Object>(root);
}


}
