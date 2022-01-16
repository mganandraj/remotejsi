//
// Created by anandrag on 1/15/2022.
//


#include <android/binder_ibinder_jni.h>
#include "JSIValueService.h"
#include "JSIStringService.h"
#include "JSIObjectService.h"
#include "JSISymbolService.h"

#include <hermes/hermes.h>
#include <jsi/jsi.h>

#define LOG_TAG "JSIValueService"
#include "logging.h"

namespace aidl::com::example::remotejsi {
JSIValueService::JSIValueService(std::shared_ptr<facebook::jsi::Runtime> runtime,
                                 facebook::jsi::Value jsValue)
        : runtime_(runtime), jsValue_(std::move(jsValue)) {}

::ndk::ScopedAStatus JSIValueService::getType(int8_t *_aidl_return) {
    // Undefined: 0
    // Null: 1
    // Boolean: 2
    // Number: 3
    // Symbol: 4
    // String: 5
    // Object: 6
    // Unknown: 255

    if(jsValue_.isUndefined()) {
        *_aidl_return = 0;
    } else if(jsValue_.isNull()) {
        *_aidl_return = 1;
    } else if(jsValue_.isBool()) {
        *_aidl_return = 2;
    }
    else if(jsValue_.isNumber()) {
        *_aidl_return = 3;
    }
    else if(jsValue_.isSymbol()) {
        *_aidl_return = 4;
    }
    else if(jsValue_.isString()) {
        *_aidl_return = 5;
    }
    else if(jsValue_.isObject()) {
        *_aidl_return = 6;
    } else {
        *_aidl_return = 255;
    }

    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIValueService::getNumber(double *_aidl_return) {
    assert(jsValue_.isNumber());
    *_aidl_return = jsValue_.getNumber();
}

::ndk::ScopedAStatus JSIValueService::getBoolean(bool *_aidl_return) {
    assert(jsValue_.isBool());
    *_aidl_return = jsValue_.getBool();
}

::ndk::ScopedAStatus JSIValueService::getString(::ndk::SpAIBinder *_aidl_return) {
    assert(jsValue_.isString());
    auto jsiStringService = ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::JSIStringService>(runtime_, jsValue_.getString(*runtime_));
    *_aidl_return = jsiStringService->asBinder();
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIValueService::getObject(::ndk::SpAIBinder *_aidl_return) {
    assert(jsValue_.isObject());
    auto jsiObjectService = ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::JSIObjectService>(runtime_, jsValue_.getObject(*runtime_));
    *_aidl_return = jsiObjectService->asBinder();
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIValueService::getSymbol(::ndk::SpAIBinder *_aidl_return) {
    assert(jsValue_.isSymbol());
    auto jsiSymbolService = ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::JSISymbolService>(runtime_, jsValue_.getSymbol(*runtime_));
    *_aidl_return = jsiSymbolService->asBinder();
    return ::ndk::ScopedAStatus::ok();
}

facebook::jsi::Value JSIValueService::copyValue() {
    return facebook::jsi::Value(*runtime_, jsValue_);
}

}