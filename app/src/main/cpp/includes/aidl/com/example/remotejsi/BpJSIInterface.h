#pragma once

#include "aidl/com/example/remotejsi/IJSIInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpJSIInterface : public ::ndk::BpCInterface<IJSIInterface> {
public:
  BpJSIInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpJSIInterface();

  ::ndk::ScopedAStatus eval(const ::ndk::SpAIBinder& in_bufferBinder, const std::string& in_sourceURL, ::ndk::SpAIBinder* _aidl_return) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
