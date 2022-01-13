#pragma once

#include "aidl/com/example/remotejsi/IJSIAidlInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnJSIAidlInterface : public ::ndk::BnCInterface<IJSIAidlInterface> {
public:
  BnJSIAidlInterface();
  virtual ~BnJSIAidlInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
