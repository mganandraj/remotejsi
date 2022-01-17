#pragma once

#include "aidl/com/example/remotejsi/IHostFunctionInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnHostFunctionInterface : public ::ndk::BnCInterface<IHostFunctionInterface> {
public:
  BnHostFunctionInterface();
  virtual ~BnHostFunctionInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
