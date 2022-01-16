#pragma once

#include "aidl/com/example/remotejsi/IJSIObjectStaticsInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpJSIObjectStaticsInterface : public ::ndk::BpCInterface<IJSIObjectStaticsInterface> {
public:
  BpJSIObjectStaticsInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpJSIObjectStaticsInterface();

  ::ndk::ScopedAStatus createObject(::ndk::SpAIBinder* _aidl_return) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
