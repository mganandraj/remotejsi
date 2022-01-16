#pragma once

#include "aidl/com/example/remotejsi/IJSIStringStaticsInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpJSIStringStaticsInterface : public ::ndk::BpCInterface<IJSIStringStaticsInterface> {
public:
  BpJSIStringStaticsInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpJSIStringStaticsInterface();

  ::ndk::ScopedAStatus createFromAscii(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createFromUtf8(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createFromNullTerminatedAscii(const std::vector<int8_t>& in_chars, ::ndk::SpAIBinder* _aidl_return) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
