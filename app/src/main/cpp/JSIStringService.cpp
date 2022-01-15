//
// Created by anandrag on 1/15/2022.
//


#include <android/binder_ibinder_jni.h>
#include "JSIStringService.h"

#include <hermes/hermes.h>
#include <jsi/jsi.h>

#define LOG_TAG "JSIStringService"
#include "logging.h"

namespace aidl::com::example::remotejsi {
JSIStringService::JSIStringService(std::shared_ptr <facebook::jsi::Runtime> runtime,
                                   facebook::jsi::String jsString)
        : runtime_(runtime), jsString_(std::move(jsString)) {}

::ndk::ScopedAStatus JSIStringService::utf8(std::string* _aidl_return) {
    *_aidl_return = jsString_.utf8(*runtime_);
    return ::ndk::ScopedAStatus::ok();
}

}
