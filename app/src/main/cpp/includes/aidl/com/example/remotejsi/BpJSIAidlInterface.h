#pragma once

#include "aidl/com/example/remotejsi/IJSIAidlInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpJSIAidlInterface : public ::ndk::BpCInterface<IJSIAidlInterface> {
public:
  BpJSIAidlInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpJSIAidlInterface();

  ::ndk::ScopedAStatus basicTypes(int32_t in_anInt, int64_t in_aLong, bool in_aBoolean, float in_aFloat, double in_aDouble, const std::string& in_aString) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
