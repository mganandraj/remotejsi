#pragma once

#include "aidl/com/example/remotejsi/IManagerInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnManagerInterface : public ::ndk::BnCInterface<IManagerInterface> {
public:
  BnManagerInterface();
  virtual ~BnManagerInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
