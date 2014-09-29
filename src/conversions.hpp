#ifndef __CONVERSIONS_HPP__

#include <v8.h>
#include <nan.h>
#include <gfcpp/PdxInstanceFactory.hpp>
#include <gfcpp/CacheFactory.hpp>
#include <string>

using namespace v8;

namespace node_gemfire {

gemfire::CacheablePtr gemfireValueFromV8(const Local<Value> & v8Value,
                                         const gemfire::CachePtr & cachePtr);
gemfire::PdxInstancePtr gemfireValueFromV8(const Local<Object> & v8Object,
                                           const gemfire::CachePtr & cachePtr);

gemfire::CacheableKeyPtr gemfireKeyFromV8(const Local<Value> & v8Value,
                                          const gemfire::CachePtr & cachePtr);
gemfire::VectorOfCacheableKeyPtr gemfireKeysFromV8(const Local<Array> & v8Value,
                                          const gemfire::CachePtr & cachePtr);

gemfire::HashMapOfCacheablePtr gemfireHashMapFromV8(const Local<Object> & v8Object,
                                           const gemfire::CachePtr & cachePtr);
gemfire::CacheableVectorPtr gemfireVectorFromV8(const Local<Array> & v8Array,
                                           const gemfire::CachePtr & cachePtr);

Local<Value> v8ValueFromGemfire(const gemfire::CacheablePtr & valuePtr);
Local<Object> v8ValueFromGemfire(const gemfire::StructPtr & structPtr);
Local<Value> v8ValueFromGemfire(const gemfire::PdxInstancePtr & pdxInstancePtr);
Local<Object> v8ValueFromGemfire(const gemfire::SelectResultsPtr & selectResultsPtr);
Local<Object> v8ValueFromGemfire(const gemfire::HashMapOfCacheablePtr & hashMapPtr);
Local<Boolean> v8ValueFromGemfire(bool value);

template<typename T>
Local<Array> v8ValueFromGemfire(const T & vectorPtr) {
  NanEscapableScope();

  unsigned int length = vectorPtr->size();

  Local<Array> array(NanNew<Array>(length));
  for (unsigned int i = 0; i < length; i++) {
    gemfire::CacheablePtr cacheablePtr((*vectorPtr)[i]);
    array->Set(i, v8ValueFromGemfire(cacheablePtr));
  }

  return NanEscapeScope(array);
}

std::string getClassName(const Local<Object> & v8Object);

}  // namespace node_gemfire

#define __CONVERSIONS_HPP__
#endif
