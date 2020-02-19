# jsonc11



### What is jsonc11?

JsonC11 using modern C++11 features to encode/decode JSON data, the following are some examples.



### Supported types

Jsonc11 supports `null` , `false`, `true` , `int`, `double`, `string`, `array`, `object`, developers should know jsonc11 not support `long int` or `long long int`



### Features

Support JSON text contains the comments such as `#` , `//` , or `/**/`



### Tools

Jsonc11 using Bison & Flex to do the lexical and the grammer job. Only contains serveral headers, if you want to using in your projects, if you need.



### Difference

The difference between current version and previous one, was that current version using `std::unique_ptr<>` to manage the memory automatically, no longer for user to free the return memory pointer



### APIs

- Decode the JSON string into Json value

```C++
static Json Json::fromJson(const std::string &json_string);
```



- Encode the Json value into JSON string, parameter was the return format: Compact or Indent

```C++
std::string toJson(Doc::Indent);
std::string toJson(Doc::Compact);
```



- Get value from Json value(array or object)

```C++
Json operator [](const char *key);
Json operator [](const std::string &key);
Json operator [](int index);
```



- Get the inner value with the inner type

```c++
std::string 	 	asString();
int 			asInt();
double  		asDouble();
bool 	  		asBool();
array 			asArray();
object  		asObject();
```



- Check the Json type

```c++
bool isNull();
bool isInt();
bool isBool();
bool isDouble();
bool isString();
bool isArray();
bool isObject();
```



- Append data into the Json type data

```C++
void arrayPush( const Json& val );
void objectAppend( Json val );
void objectAppend( const std::string &key, Json val );
```



#### Decoding Example

```C++
#include <iostream>
#include "json.h"

int main()
{
    Json v = Json::fromJson(R"(
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
    if ( v.hasError() ) {
      std::cout << v.getErrors();
    } else {
      std::cout << v.toJson( Doc::Compact );
    }

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

