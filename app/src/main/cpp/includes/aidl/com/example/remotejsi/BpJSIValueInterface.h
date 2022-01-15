#pragma once

#include "aidl/com/example/remotejsi/IJSIValueInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpJSIValueInterface : public ::ndk::BpCInterface<IJSIValueInterface> {
public:
  BpJSIValueInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpJSIValueInterface();

  ::ndk::ScopedAStatus getType(int8_t* _aidl_return) override;
  ::ndk::ScopedAStatus getNumber(double* _aidl_return) override;
  ::ndk::ScopedAStatus getBoolean(bool* _aidl_return) override;
  ::ndk::ScopedAStatus getString(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus getObject(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus getSymbol(::ndk::SpAIBinder* _aidl_return) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
