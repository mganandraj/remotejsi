#pragma once

#include "aidl/com/example/remotejsi/IJSIStringInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnJSIStringInterface : public ::ndk::BnCInterface<IJSIStringInterface> {
public:
  BnJSIStringInterface();
  virtual ~BnJSIStringInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
