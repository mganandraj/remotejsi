#pragma once

#include "aidl/com/example/remotejsi/IValueCollectionInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnValueCollectionInterface : public ::ndk::BnCInterface<IValueCollectionInterface> {
public:
  BnValueCollectionInterface();
  virtual ~BnValueCollectionInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
