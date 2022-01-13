#pragma once

#include "aidl/com/example/remotejsi/IJSIInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnJSIInterface : public ::ndk::BnCInterface<IJSIInterface> {
public:
  BnJSIInterface();
  virtual ~BnJSIInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
