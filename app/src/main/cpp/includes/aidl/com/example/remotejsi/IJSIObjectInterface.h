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
class IJSIObjectInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IJSIObjectInterface();
  virtual ~IJSIObjectInterface();



  static std::shared_ptr<IJSIObjectInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IJSIObjectInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IJSIObjectInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IJSIObjectInterface> impl);
  static const std::shared_ptr<IJSIObjectInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus has(const ::ndk::SpAIBinder& in_name, bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus get(const ::ndk::SpAIBinder& in_name, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus set(const ::ndk::SpAIBinder& in_name, const ::ndk::SpAIBinder& in_value) = 0;
private:
  static std::shared_ptr<IJSIObjectInterface> default_impl;
};
class IJSIObjectInterfaceDefault : public IJSIObjectInterface {
public:
  ::ndk::ScopedAStatus has(const ::ndk::SpAIBinder& in_name, bool* _aidl_return) override;
  ::ndk::ScopedAStatus get(const ::ndk::SpAIBinder& in_name, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus set(const ::ndk::SpAIBinder& in_name, const ::ndk::SpAIBinder& in_value) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
