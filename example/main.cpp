
#include "../sources/jwt.h"
#include "../sources/algo/hmac.h"
#include <iostream>

using jwt::Token;
using jwt::Hmac;
int main () {

    Token j(new Hmac(jwt::sha256, "noegle"));

    auto c = j.claims();
    c->set("sub", std::string("123303"));
    c->set("age", 32);
    c->set("hello",3.2);
    c->set("Hello", "hello");
    jwt::Object o;
    o.set("name", "Rasmus Kildevæld");
    o.set("age", 32);
    o.set("Hello", false);
    c->set("person", o);


    std::cout << c->encode() << std::endl;


    //std::cout << c->get<std::string>("sub") << std::endl;

    auto payload = j.encode();

    std::cout << "Token: " << payload << std::endl;

    jwt::decode(new Hmac(jwt::sha256, "noegle"), payload);



}
