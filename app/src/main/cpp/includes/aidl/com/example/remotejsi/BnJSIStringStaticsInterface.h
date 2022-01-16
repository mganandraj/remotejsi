#pragma once

#include "aidl/com/example/remotejsi/IJSIStringStaticsInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnJSIStringStaticsInterface : public ::ndk::BnCInterface<IJSIStringStaticsInterface> {
public:
  BnJSIStringStaticsInterface();
  virtual ~BnJSIStringStaticsInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
