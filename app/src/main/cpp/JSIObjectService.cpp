//
// Created by anandrag on 1/15/2022.
//


#include <android/binder_ibinder_jni.h>
#include "JSIObjectService.h"
#include "JSIStringService.h"
#include "JSIValueService.h"

#include <hermes/hermes.h>
#include <jsi/jsi.h>

#define LOG_TAG "JSIObjectService"
#include "logging.h"

namespace aidl::com::example::remotejsi {
    JSIObjectService::JSIObjectService(std::shared_ptr <facebook::jsi::Runtime> runtime,
                                       facebook::jsi::Object jsObject)
            : runtime_(runtime), jsObject_(std::move(jsObject)) {}

    facebook::jsi::Object JSIObjectService::copyObject() {
        return facebook::jsi::Value(*runtime_, jsObject_).getObject(*runtime_);
    }

    ::ndk::ScopedAStatus JSIObjectService::has(const ::ndk::SpAIBinder& in_name, bool* _aidl_return) {
        auto propNameStringService = aidl::com::example::remotejsi::JSIStringService::fromBinder(in_name);
        std::string propName;
        propNameStringService->utf8(&propName); // TODO:: Directly reference the jsi::String instead of extracting the utf8
        *_aidl_return = jsObject_.hasProperty(*runtime_, propName.c_str());

        return ::ndk::ScopedAStatus::ok();
    }

    ::ndk::ScopedAStatus JSIObjectService::get(const ::ndk::SpAIBinder& in_name, ::ndk::SpAIBinder* _aidl_return) {
        auto propNameStringService = aidl::com::example::remotejsi::JSIStringService::fromBinder(in_name);
        std::string propName;
        propNameStringService->utf8(&propName); // TODO:: Directly reference the jsi::String instead of extracting the utf8
        facebook::jsi::Value value = jsObject_.getProperty(*runtime_, propName.c_str());

        auto jsiValueService = ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::JSIValueService>(runtime_, std::move(value));
        *_aidl_return = jsiValueService->asBinder();

        return ::ndk::ScopedAStatus::ok();
    }

    ::ndk::ScopedAStatus JSIObjectService::set(const ::ndk::SpAIBinder& in_name, const ::ndk::SpAIBinder& in_value) {
        auto propNameStringService = aidl::com::example::remotejsi::JSIStringService::fromBinder(in_name);
        std::string propName;
        propNameStringService->utf8(&propName);

        auto jsiValueService = aidl::com::example::remotejsi::JSIValueService::fromBinder(in_value);
        JSIValueService* jsiValueService1 = static_cast<JSIValueService*>(jsiValueService.get());
        // IJSIStringInterface* pijsiValueInterface = jsiValueService.get();
        // JSIStringService* pjsiValueInterface = static_cast<JSIStringService*>(pijsiValueInterface);

        jsObject_.setProperty(*runtime_, propName.c_str(), jsiValueService1->copyValue());
        return ::ndk::ScopedAStatus::ok();
    }
}