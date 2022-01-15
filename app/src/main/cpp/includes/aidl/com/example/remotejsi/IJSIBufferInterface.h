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
class IJSIBufferInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IJSIBufferInterface();
  virtual ~IJSIBufferInterface();



  static std::shared_ptr<IJSIBufferInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IJSIBufferInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IJSIBufferInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IJSIBufferInterface> impl);
  static const std::shared_ptr<IJSIBufferInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus data(std::vector<int8_t>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus size(int64_t* _aidl_return) = 0;
private:
  static std::shared_ptr<IJSIBufferInterface> default_impl;
};
class IJSIBufferInterfaceDefault : public IJSIBufferInterface {
public:
  ::ndk::ScopedAStatus data(std::vector<int8_t>* _aidl_return) override;
  ::ndk::ScopedAStatus size(int64_t* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
