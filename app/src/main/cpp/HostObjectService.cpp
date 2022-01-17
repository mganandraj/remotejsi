//
// Created by anandrag on 1/17/2022.
//

#include "HostObjectService.h"


#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIBufferInterface.h>

#define LOG_TAG "JSIBufferService"
#include "logging.h"

#include <jsi/jsi.h>

namespace aidl::com::example::remotejsi {

HostObjectService::HostObjectService(std::shared_ptr<facebook::jsi::HostObject> ho): ho_(std::move(ho)) {
    //
}

::ndk::ScopedAStatus HostObjectService::get(const ::ndk::SpAIBinder &in_name, ::ndk::SpAIBinder *_aidl_return) {
    // TODO
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus HostObjectService::set(const ::ndk::SpAIBinder &in_name, const ::ndk::SpAIBinder &in_value) {
    // TODO
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus HostObjectService::getPropertyNames() {
    // TODO
    return ::ndk::ScopedAStatus::ok();
}

}
