
#include "claim.h"
#include "rapidjson/document.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h" // for stringify JSON

using namespace rapidjson;
#include <iostream>

namespace jwt {

/*const char *ClaimSet::encode() const
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    writer.StartObject();
    for (auto kv: m_map) {
        writer.String(kv.first);
        Any second = kv.second;

        if (second.is<string>()) {
            writer.String(second.as<string>().c_str());
        } else if (second.is<const char*>()) {
            writer.String(second.as<const char*>());
        } else if (second.is<int>()) {
            writer.Int(second.as<int>());
        }
    }
    writer.EndObject();

    return sb.GetString();
}*/

}
