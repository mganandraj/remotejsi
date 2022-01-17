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
class IValueCollectionInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IValueCollectionInterface();
  virtual ~IValueCollectionInterface();



  static std::shared_ptr<IValueCollectionInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IValueCollectionInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IValueCollectionInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IValueCollectionInterface> impl);
  static const std::shared_ptr<IValueCollectionInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus add(const ::ndk::SpAIBinder& in_value) = 0;
  virtual ::ndk::ScopedAStatus get(int64_t in_index, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getCount(int64_t* _aidl_return) = 0;
private:
  static std::shared_ptr<IValueCollectionInterface> default_impl;
};
class IValueCollectionInterfaceDefault : public IValueCollectionInterface {
public:
  ::ndk::ScopedAStatus add(const ::ndk::SpAIBinder& in_value) override;
  ::ndk::ScopedAStatus get(int64_t in_index, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus getCount(int64_t* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
