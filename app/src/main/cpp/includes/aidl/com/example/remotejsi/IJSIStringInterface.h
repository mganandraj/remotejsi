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
class IJSIStringInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IJSIStringInterface();
  virtual ~IJSIStringInterface();



  static std::shared_ptr<IJSIStringInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IJSIStringInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IJSIStringInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IJSIStringInterface> impl);
  static const std::shared_ptr<IJSIStringInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus utf8(std::string* _aidl_return) = 0;
private:
  static std::shared_ptr<IJSIStringInterface> default_impl;
};
class IJSIStringInterfaceDefault : public IJSIStringInterface {
public:
  ::ndk::ScopedAStatus utf8(std::string* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
