//
// Created by anandrag on 1/15/2022.
//


#include <android/binder_ibinder_jni.h>
#include "JSIObjectService.h"

#include <hermes/hermes.h>
#include <jsi/jsi.h>

#define LOG_TAG "JSIObjectService"
#include "logging.h"

namespace aidl::com::example::remotejsi {
    JSIObjectService::JSIObjectService(std::shared_ptr <facebook::jsi::Runtime> runtime,
                                       facebook::jsi::Object jsObject)
            : runtime_(runtime), jsObject_(std::move(jsObject)) {}
}