#pragma once

#include "aidl/com/example/remotejsi/IJSIStringInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpJSIStringInterface : public ::ndk::BpCInterface<IJSIStringInterface> {
public:
  BpJSIStringInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpJSIStringInterface();

  ::ndk::ScopedAStatus utf8(std::string* _aidl_return) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
