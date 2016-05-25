
#include "../sources/jwt.h"
#include "../sources/algo/hmac.h"
#include <iostream>

using jwt::Token;
using jwt::Hmac;
int main () {

    Token j(new Hmac(jwt::sha256, "nogle"));

    j.set_claim("age", 32);
    j.set_claim("hello", "world");
    //auto c = j.claims();
    /*c->set("sub", std::string("123303"));
    c->set("age", 32);
    c->set("hello",3.2);
    c->set("Hello", "hello");
    jwt::Object o;
    o.set("name", "Rasmus Kildevæld");
    o.set("age", 32);
    o.set("Hello", false);
    c->set("person", o);*/
    //c["age"] = 32;
    //c["hello"] = "Hello";


    //std::cout << c.dump() << std::endl;


    //std::cout << c->get<std::string>("sub") << std::endl;

    auto payload = j.encode();

    std::cout << "Token: " << payload << std::endl;

    auto js = jwt::decode(new Hmac(jwt::sha256, "nogle"), payload);

    std::cout << "\n" << js->get_claim<int>("age") << std::endl;

}
