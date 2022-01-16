#pragma once

#include "aidl/com/example/remotejsi/IJSIObjectInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpJSIObjectInterface : public ::ndk::BpCInterface<IJSIObjectInterface> {
public:
  BpJSIObjectInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpJSIObjectInterface();

  ::ndk::ScopedAStatus has(const ::ndk::SpAIBinder& in_name, bool* _aidl_return) override;
  ::ndk::ScopedAStatus get(const ::ndk::SpAIBinder& in_name, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus set(const ::ndk::SpAIBinder& in_name, const ::ndk::SpAIBinder& in_value) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
