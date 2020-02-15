# jsonc11



### What is jsonc11?

JsonC11 using modern C++11 feature to encode/decode JSON data, the following is the example.



### Features

Support JSON text contains the comments such as `#` , `//` , or `/**/`



### Tools

Jsonc11 using Bison & Flex to do the lexical and the grammer job. Only contains serveral headers, if you want to using in your projects, if you need.



#### Decoding Example

```C++
#include <iostream>
#include "json.h"

int main()
{
    Json *v = Json::fromJson(R"(
{
    "a":"bb",
    "b":"cc",
    "c":"dd",
    "d": [ "Linux", "macOS", "Windows" ],
    "e": { "name":"Qedis", "version":"v1.0.1", "feature":"Quick & Easy for using" },
    "f": [ "aa", "bb", "cc", [ "dd", "ee", "ff" ], [ "gg", "hh" ] ],
    "g": { "kk":"unix" }
}
)");
    if ( v->hasError() ) {
      std::cout << v->getErrors();
    } else {
      std::cout << v->toJson( Doc::Compact );
    }

    // You shall free the returned memory to forbid memory leak
    delete v;

    return 0;
}
```

##### Output

```
{"a":"bb","b":"cc","c":"dd","d":["Linux","macOS","Windows"],"e":{"feature":"Quick & Easy to use","name":"Qedis","version":"v1.0.1"},"f":["aa","bb","cc",["dd","ee","ff"],["gg","hh"]],"g":{"kk":"unix"}}
```



#### Encoding Example

```C++
#include <iostream>
#include "json.h"

int main()
{
    
    Json v = Json::object({
        { "name", "c++11"},
        { "prop", "fast"},
        { "test", Json::array({ 11, 22, 33 })}
    });
    
  	// toJson() contains one parameter to decide the return json format compact or indent
    std::cout << v.toJson(Doc::Indent); // Also Doc::Compact shows in the previous example

    return 0;
}
```

##### Output

```
{
	"name":"c++11",
	"prop":"fast",
	"test":[
	    11,
            22,
	    33
	]
}
```

