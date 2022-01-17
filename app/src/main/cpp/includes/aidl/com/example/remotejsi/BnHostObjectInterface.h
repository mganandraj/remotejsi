#pragma once

#include "aidl/com/example/remotejsi/IHostObjectInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnHostObjectInterface : public ::ndk::BnCInterface<IHostObjectInterface> {
public:
  BnHostObjectInterface();
  virtual ~BnHostObjectInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
