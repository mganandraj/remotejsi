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

  ::ndk::ScopedAStatus basicTypes(int32_t in_anInt, int64_t in_aLong, bool in_aBoolean, float in_aFloat, double in_aDouble, const std::string& in_aString) override;
  ::ndk::ScopedAStatus handshake(const ::ndk::SpAIBinder& in_remoteJSIInterface) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
