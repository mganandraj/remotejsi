#pragma once

#include "aidl/com/example/remotejsi/IJSISymbolInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpJSISymbolInterface : public ::ndk::BpCInterface<IJSISymbolInterface> {
public:
  BpJSISymbolInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpJSISymbolInterface();

};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
