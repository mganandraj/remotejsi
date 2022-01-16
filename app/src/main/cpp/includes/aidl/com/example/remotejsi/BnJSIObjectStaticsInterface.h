#pragma once

#include "aidl/com/example/remotejsi/IJSIObjectStaticsInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnJSIObjectStaticsInterface : public ::ndk::BnCInterface<IJSIObjectStaticsInterface> {
public:
  BnJSIObjectStaticsInterface();
  virtual ~BnJSIObjectStaticsInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
