#pragma once

#include "aidl/com/example/remotejsi/IJSIInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpJSIInterface : public ::ndk::BpCInterface<IJSIInterface> {
public:
  BpJSIInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpJSIInterface();

  ::ndk::ScopedAStatus eval(const ::ndk::SpAIBinder& in_bufferBinder, const std::string& in_sourceURL, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createObject(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus cloneValue(int8_t in_valueType, bool in_boolValue, double in_doubleValue, const ::ndk::SpAIBinder& in_pointerBinder, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createFromAscii(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createFromUtf8(const std::vector<int8_t>& in_bytes, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createValueCollection(::ndk::SpAIBinder* _aidl_return) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
