#pragma once

#include "aidl/com/example/remotejsi/IJSISymbolInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnJSISymbolInterface : public ::ndk::BnCInterface<IJSISymbolInterface> {
public:
  BnJSISymbolInterface();
  virtual ~BnJSISymbolInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
