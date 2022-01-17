//
// Created by anandrag on 1/17/2022.
//

#ifndef REMOTEJSI_HOSTFUNCTIONSERVICE_H
#define REMOTEJSI_HOSTFUNCTIONSERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnHostFunctionInterface.h>

#include <jsi/jsi.h>

namespace aidl::com::example::remotejsi {
class HostFunctionService : public BnHostFunctionInterface {
public:
    HostFunctionService(facebook::jsi::HostFunctionType&& function);
    ::ndk::ScopedAStatus call(const ::ndk::SpAIBinder& in_thisVal, const std::shared_ptr<::aidl::com::example::remotejsi::IValueCollectionInterface>& in_args,
                              int64_t in_size, ::ndk::SpAIBinder* _aidl_return);

private:
    facebook::jsi::HostFunctionType hostFunction_;
};
}

#endif //REMOTEJSI_HOSTFUNCTIONSERVICE_H
