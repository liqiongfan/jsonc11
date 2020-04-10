#include <iostream>
#include "json.h"

int main()
{
    
    for ( int i = 0; i < 1; ++i ) {
        Json v = Json::fromJson(R"(
{
    "a":"bb",// Hello world
    "b":"cc",# This is my Json parser tool
/*
Hello world, C++ comments coming*/
    //"c":"dd",
    "d": [ "Linux", "macOS", "Windows" ],
    "e": { "name":"Qedis", "version":"v1.0.1", "feature":"Quick & Easy to use" },
    "f": [ "aa", "bb", "cc", [ "dd", "ee", "ff" ], [ "gg", "hh" ] ],
    "g": { "kk":"unix" }
}
)");
        if ( v.hasError() ) {
            std::cout << v.getErrors();
        } else {
            std::cout << v.toJson( Doc::Indent );
        }
       
    }

    return 0;
}
