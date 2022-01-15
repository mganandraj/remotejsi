#pragma once

#include "aidl/com/example/remotejsi/IJSIObjectInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnJSIObjectInterface : public ::ndk::BnCInterface<IJSIObjectInterface> {
public:
  BnJSIObjectInterface();
  virtual ~BnJSIObjectInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
