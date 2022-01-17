//
// Created by anandrag on 1/17/2022.
//

#ifndef REMOTEJSI_HOSTOBJECTSERVICE_H
#define REMOTEJSI_HOSTOBJECTSERVICE_H


#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnHostObjectInterface.h>

#include <jsi/jsi.h>

namespace aidl::com::example::remotejsi {
class HostObjectService : public BnHostObjectInterface {
public:
    HostObjectService(std::shared_ptr<facebook::jsi::HostObject> ho);

    ::ndk::ScopedAStatus get(const ::ndk::SpAIBinder& in_name, ::ndk::SpAIBinder* _aidl_return) override;
    ::ndk::ScopedAStatus set(const ::ndk::SpAIBinder& in_name, const ::ndk::SpAIBinder& in_value) override;
    ::ndk::ScopedAStatus getPropertyNames() override;

private:
    std::shared_ptr<facebook::jsi::HostObject> ho_;
};
}

#endif //REMOTEJSI_HOSTOBJECTSERVICE_H
