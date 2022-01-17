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
#include <aidl/com/example/remotejsi/IValueCollectionInterface.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class IHostObjectInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IHostObjectInterface();
  virtual ~IHostObjectInterface();



  static std::shared_ptr<IHostObjectInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IHostObjectInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IHostObjectInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IHostObjectInterface> impl);
  static const std::shared_ptr<IHostObjectInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus get(const ::ndk::SpAIBinder& in_name, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus set(const ::ndk::SpAIBinder& in_name, const ::ndk::SpAIBinder& in_value) = 0;
  virtual ::ndk::ScopedAStatus getPropertyNames() = 0;
private:
  static std::shared_ptr<IHostObjectInterface> default_impl;
};
class IHostObjectInterfaceDefault : public IHostObjectInterface {
public:
  ::ndk::ScopedAStatus get(const ::ndk::SpAIBinder& in_name, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus set(const ::ndk::SpAIBinder& in_name, const ::ndk::SpAIBinder& in_value) override;
  ::ndk::ScopedAStatus getPropertyNames() override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
