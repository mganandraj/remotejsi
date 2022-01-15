#pragma once

#include "aidl/com/example/remotejsi/IJSIBufferInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnJSIBufferInterface : public ::ndk::BnCInterface<IJSIBufferInterface> {
public:
  BnJSIBufferInterface();
  virtual ~BnJSIBufferInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
