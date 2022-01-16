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
class IJSIObjectStaticsInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IJSIObjectStaticsInterface();
  virtual ~IJSIObjectStaticsInterface();



  static std::shared_ptr<IJSIObjectStaticsInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IJSIObjectStaticsInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IJSIObjectStaticsInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IJSIObjectStaticsInterface> impl);
  static const std::shared_ptr<IJSIObjectStaticsInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus createObject(::ndk::SpAIBinder* _aidl_return) = 0;
private:
  static std::shared_ptr<IJSIObjectStaticsInterface> default_impl;
};
class IJSIObjectStaticsInterfaceDefault : public IJSIObjectStaticsInterface {
public:
  ::ndk::ScopedAStatus createObject(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
