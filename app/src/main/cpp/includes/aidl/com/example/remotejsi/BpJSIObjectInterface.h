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

};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
