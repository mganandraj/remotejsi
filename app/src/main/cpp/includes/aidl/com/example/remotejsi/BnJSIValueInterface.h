#pragma once

#include "aidl/com/example/remotejsi/IJSIValueInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnJSIValueInterface : public ::ndk::BnCInterface<IJSIValueInterface> {
public:
  BnJSIValueInterface();
  virtual ~BnJSIValueInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
