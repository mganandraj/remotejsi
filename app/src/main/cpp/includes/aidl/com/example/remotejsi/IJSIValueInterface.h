#pragma once

#include <android/binder_interface_utils.h>

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class IJSIValueInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IJSIValueInterface();
  virtual ~IJSIValueInterface();



  static std::shared_ptr<IJSIValueInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IJSIValueInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IJSIValueInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IJSIValueInterface> impl);
  static const std::shared_ptr<IJSIValueInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus getType(int8_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getNumber(double* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getBoolean(bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getString(::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getObject(::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getSymbol(::ndk::SpAIBinder* _aidl_return) = 0;
private:
  static std::shared_ptr<IJSIValueInterface> default_impl;
};
class IJSIValueInterfaceDefault : public IJSIValueInterface {
public:
  ::ndk::ScopedAStatus getType(int8_t* _aidl_return) override;
  ::ndk::ScopedAStatus getNumber(double* _aidl_return) override;
  ::ndk::ScopedAStatus getBoolean(bool* _aidl_return) override;
  ::ndk::ScopedAStatus getString(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus getObject(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus getSymbol(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
