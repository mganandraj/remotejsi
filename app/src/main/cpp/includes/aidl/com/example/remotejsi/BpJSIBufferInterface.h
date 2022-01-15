#pragma once

#include "aidl/com/example/remotejsi/IJSIBufferInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpJSIBufferInterface : public ::ndk::BpCInterface<IJSIBufferInterface> {
public:
  BpJSIBufferInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpJSIBufferInterface();

  ::ndk::ScopedAStatus data(std::vector<int8_t>* _aidl_return) override;
  ::ndk::ScopedAStatus size(int64_t* _aidl_return) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
