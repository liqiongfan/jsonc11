#ifndef BSON_JSON_H
#define BSON_JSON_H

#include <map>
#include <vector>
#include <list>
#include <string>

// Json parse function
struct Json;
extern Json *_parse(const std::string &json_string);

// Json decode/encode class
struct Json
{
    // Value type
    enum class Type {
        T_NULL   = 1, T_INT = 2, T_BOOL = 3,
        T_DOUBLE = 4, T_STRING = 5, T_ARRAY = 6,
        T_OBJECT = 7
    };
    
    // Return Json type
    enum class JsonType { Indent = 1, Compact = 2 };
    
    // Inner Type
    typedef std::vector<Json> array;
    typedef std::map<std::string, Json> object;
    
    // Get the Type
    Type getType();
    
    // Constructor
    Json();                    // Null
    Json(int);                 // Int
    Json(bool);                // Bool
    Json(double);              // Double
    Json(const char *value);   // String
    Json(std::string &&value); // String
    Json(array &&array);       // Array
    Json(const array &array);  // Array
    Json(object &&object);     // Object
    ~Json();
    
    // Some method for typeChecks
    bool isNull() { return this->type == Type::T_NULL; }
    bool isInt()  { return this->type == Type::T_INT;  }
    bool isBool() { return this->type == Type::T_BOOL; }
    bool isDouble() { return this->type == Type::T_DOUBLE; }
    bool isString() { return this->type == Type::T_STRING; }
    bool isArray() { return this->type == Type::T_ARRAY;   }
    bool isObject() { return this->type == Type::T_OBJECT; }
    
    // Add data to Collection
    void arrayPush(const Json& val);
    void objectAppend( Json val );
    void objectAppend( const std::string &key, Json val );
    
    // Format to Json string
    std::string toJson(JsonType jsonType = JsonType::Compact );
    
    // Parse JSON from JSON string
    static Json *fromJson(const std::string &json) {
        return _parse(json);
    }
    // Parse error
    Json *setParseError(const std::string &error);
    // Please use && to get the return value
    std::string getErrors();
    // To get wheather the parsing step is successfull or not
    bool hasError();
    
private:
    Type type;
    bool  parseError{false};
    std::string      errors;
    
    // Some inner variable to store data
    int            intVal{};
    bool          boolVal{};
    double      doubleVal{};
    std::string   stringVal;
    array          arrayVal;
    object        objectVal;
    
    // For inner invoking
    std::string combineJson(JsonType jsonType = JsonType::Compact ) const;
};

// Display format: Indent or Compact mode
typedef Json::JsonType Doc;

template <typename T>
struct Stack {
    void push(T *v);
    void pop();
    T*   top();
    
    Stack();
    ~Stack();

private:
    Stack  *next;
    T      *data;
    Stack  *topV;
    int    len{};
};

template<typename T>
Stack<T>::Stack() {
    this->next = nullptr;
    this->data = nullptr;
    this->topV = nullptr;
    this->len  = 0;
}

template<typename T>
Stack<T>::~Stack() {
    if ( this->len ) {
        Stack *n = this->topV->next;
        while (n) {
            Stack *v = n->next;
            delete n;
            n = v;
        }
        delete this->topV;
    }
}

template<typename T>
void Stack<T>::push( T *v ) {
    auto *t = new Stack<T>();
    t->data = v;
    if ( this->topV != nullptr ) {
        t->next = this->topV;
        this->topV = t;
    } else {
        this->topV = t;
    }
    this->len++;
}

template<typename T>
void Stack<T>::pop() {
    if ( this->len ) {
        Stack *n = this->topV->next;
        /* delete this->topV->data; */
        delete this->topV;
        this->topV = n;
        this->len--;
    }
}

template<typename T>
T *Stack<T>::top() {
    if ( this->len ) {
        return this->topV->data;
    }
    return nullptr;
}

#endif //BSON_JSON_H
