#pragma once

#include "aidl/com/example/remotejsi/IValueCollectionInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpValueCollectionInterface : public ::ndk::BpCInterface<IValueCollectionInterface> {
public:
  BpValueCollectionInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpValueCollectionInterface();

  ::ndk::ScopedAStatus add(const ::ndk::SpAIBinder& in_value) override;
  ::ndk::ScopedAStatus get(int64_t in_index, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus getCount(int64_t* _aidl_return) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
