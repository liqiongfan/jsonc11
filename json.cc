#include <iostream>
#include <sstream>
#include "json.h"


// Obtain the JsonValue Type
Json::Type Json::getType() {
    return this->type;
}

Json::Json()
{
    // For null, it's no variable to store
    this->type = Type::T_NULL;
}

Json::Json( int val )
{
    // For int val, store into the intVal
    this->intVal = val;
    this->type = Type::T_INT;
}

Json::Json( bool val )
{
    // For bool val, store into boolVal
    this->boolVal = val;
    this->type = Type::T_BOOL;
}

Json::Json( double val )
{
    // For double val, store into doubleVal
    this->doubleVal = val;
    this->type = Type::T_DOUBLE;
}

Json::Json( const char *value )
{
    this->type = Type::T_STRING;
    this->stringVal = std::move(std::string(value));
}

Json::Json( std::string &&value )
{
    this->stringVal = value;
    this->type = Type::T_STRING;
}

Json::Json( Json::array &&array )
{
    this->arrayVal = array;
    this->type = Type::T_ARRAY;
}

Json::Json( Json::object &&object )
{
    this->objectVal = object;
    this->type = Type::T_OBJECT;
}

std::string Json::combineJson( Json::JsonType jsonType ) const
{
    std::string combineJsonResp({});
    static std::string indent({});
    
    switch ( this->type ) {
        case Type::T_NULL:
            combineJsonResp.append("null");
            break;
        case Type::T_INT:
            combineJsonResp.append(std::to_string(this->intVal));
            break;
        case Type::T_BOOL:
            if ( this->boolVal ) {
                combineJsonResp.append("true");
            } else {
                combineJsonResp.append("false");
            }
            break;
        case Type::T_DOUBLE:
        {
            std::ostringstream oss;
            oss.precision(16);
            oss << this->doubleVal;
            combineJsonResp.append( oss.str() );
            break;
        }
        case Type::T_STRING:
            combineJsonResp.append("\"" + this->stringVal + "\"");
            break;
        case Type::T_OBJECT:
            combineJsonResp.append("{");
            if ( jsonType == JsonType::Indent ) { indent.append("\t"); combineJsonResp.append("\n").append(indent); }
            for ( auto iter = this->objectVal.begin(); iter != this->objectVal.end(); ) {
                
                combineJsonResp.append("\"" + iter->first + "\":");
                combineJsonResp.append(iter->second.combineJson(jsonType));
                
                iter++;
                if ( iter != this->objectVal.end() ) {
                    combineJsonResp.append( "," );
                    if ( jsonType == JsonType::Indent ) {
                        combineJsonResp.append("\n").append(indent);
                    }
                }
            }
            if ( jsonType == JsonType::Indent ) { indent = indent.erase(0, 1); combineJsonResp.append("\n").append(indent); }
            combineJsonResp.append("}");
            break;
        case Type::T_ARRAY:
            combineJsonResp.append("[");
            if ( jsonType == JsonType::Indent ) { indent.append("\t"); combineJsonResp.append("\n").append(indent); }
            for ( auto iter = this->arrayVal.begin(); iter != this->arrayVal.end(); ) {
                combineJsonResp.append(iter->combineJson(jsonType));
                
                iter++;
                if ( iter != this->arrayVal.end() ) {
                    combineJsonResp.append( "," );
                    if ( jsonType == JsonType::Indent ) {
                        combineJsonResp.append("\n").append(indent);
                    }
                }
            }
            if ( jsonType == JsonType::Indent ) { indent = indent.erase(0, 1); combineJsonResp.append("\n").append(indent); }
            combineJsonResp.append("]");
            break;
    }
    
    return combineJsonResp;
}

std::string Json::toJson( Json::JsonType jsonType )
{
    return this->combineJson(jsonType);
}

Json::Json( const Json::array &array )
{
    this->type = Type::T_ARRAY;
    this->arrayVal = array;
}

void Json::arrayPush( const Json& val )
{
    return this->arrayVal.push_back(val);
}

void Json::objectAppend( Json val )
{
    return this->objectVal.insert(val.objectVal.begin(), val.objectVal.end());
}

void Json::objectAppend( const std::string &key, Json val )
{
    this->objectVal.insert(std::pair<std::string, Json>(key, val));
}

Json *Json::setParseError( const std::string &error )
{
    this->parseError =  true;
    this->errors     = error;
    return              this;
}

std::string Json::getErrors()
{
    return this->errors;
}

bool Json::hasError()
{
    return this->parseError;
}

Json::~Json() {
    this->arrayVal.erase(this->arrayVal.begin(), this->arrayVal.end());
    this->objectVal.erase(this->objectVal.begin(), this->objectVal.end());
}

Json Json::operator []( const std::string &key ) {
    if ( this->isObject() ) {
        return this->objectVal[ key ];
    }
    throw std::bad_cast();
}

Json Json::operator []( int i ) {
    if ( this->isArray() ) {
        return this->arrayVal[i];
    }
    throw std::bad_cast();
}

Json Json::operator []( const char *key ) {
    if ( this->isObject() ) {
        return this->objectVal[key];
    }
    throw std::bad_cast();
}

std::string Json::asString() {
    if ( this->isString() ) {
        return this->stringVal;
    }
    throw std::bad_cast();
}

int Json::asInt() {
    if ( this->isInt() ) {
        return this->intVal;
    }
    throw std::bad_cast();
}

double Json::asDouble() {
    if ( this->isDouble() ) {
        return this->doubleVal;
    }
    throw std::bad_cast();
}

bool Json::asBool() {
    if ( this->isBool() ) {
        return this->boolVal;
    }
    throw std::bad_cast();
}

Json::array Json::asArray() {
    if ( this->isArray() ) {
        return this->arrayVal;
    }
    throw std::bad_cast();
}

Json::object Json::asObject() {
    if ( this->isObject() ) {
        return this->objectVal;
    }
    throw std::bad_cast();
}

