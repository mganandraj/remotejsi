//
// Created by anandrag on 1/17/2022.
//

#include "JSIValueCollectionService.h"


#include <android/binder_ibinder_jni.h>
#include "JSIValueService.h"
#include "JSIStringService.h"
#include "JSIObjectService.h"
#include "JSISymbolService.h"

#include "JSIValueCollectionService.h"

#include <hermes/hermes.h>
#include <jsi/jsi.h>

#define LOG_TAG "JSIValueService"
#include "logging.h"

namespace aidl::com::example::remotejsi {

JSIValueCollectionService::JSIValueCollectionService(std::shared_ptr <facebook::jsi::Runtime> runtime)
        : runtime_(std::move(runtime)) {}

::ndk::ScopedAStatus JSIValueCollectionService::add(const ::ndk::SpAIBinder& in_value) {
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIValueCollectionService::get(int64_t in_index, ::ndk::SpAIBinder* _aidl_return) {
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIValueCollectionService::getCount(int64_t* _aidl_return) {
    return ::ndk::ScopedAStatus::ok();
}


}