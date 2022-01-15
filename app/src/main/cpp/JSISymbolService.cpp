//
// Created by anandrag on 1/15/2022.
//


#include <android/binder_ibinder_jni.h>
#include "JSISymbolService.h"

#include <hermes/hermes.h>
#include <jsi/jsi.h>

#define LOG_TAG "JSISymbolService"
#include "logging.h"

namespace aidl::com::example::remotejsi {
    JSISymbolService::JSISymbolService(std::shared_ptr <facebook::jsi::Runtime> runtime,
                                       facebook::jsi::Symbol jsValue)
            : runtime_(runtime), jsSymbol_(std::move(jsValue)) {}
}