//
// Created by anandrag on 1/17/2022.
//

#include "HostFunctionService.h"

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIBufferInterface.h>

#define LOG_TAG "JSIBufferService"
#include "logging.h"

#include <jsi/jsi.h>

namespace aidl::com::example::remotejsi {

HostFunctionService::HostFunctionService(facebook::jsi::HostFunctionType && function) : hostFunction_(function) {}

::ndk::ScopedAStatus HostFunctionService::call(const ::ndk::SpAIBinder &in_thisVal,
                          const std::shared_ptr<::aidl::com::example::remotejsi::IValueCollectionInterface> &in_args,
                          int64_t in_size, ::ndk::SpAIBinder *_aidl_return) {
    return ::ndk::ScopedAStatus::ok();
    // TODO
}

}