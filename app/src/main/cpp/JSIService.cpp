//
// Created by anandrag on 1/12/2022.
//

#include <android/binder_ibinder_jni.h>
#include "JSIService.h"
#include "RemoteJSIService.h"
#include "JSIBufferService.h"
#include "JSIValueService.h"
#include "JSIObjectService.h"
#include "JSIStringService.h"
#include "JSISymbolService.h"

#include <hermes/hermes.h>
#include <jsi/jsi.h>

#define LOG_TAG "remotejsi-nativejsiservice"
#include "logging.h"

class JSI_EXPORT StringBuffer : public facebook::jsi::Buffer {
public:
    StringBuffer(std::string s) : s_(std::move(s)) {}
    size_t size() const override {
        return s_.size();
    }
    const uint8_t* data() const override {
        return reinterpret_cast<const uint8_t*>(s_.data());
    }

private:
    std::string s_;
};

;


namespace aidl::com::example::remotejsi {

class JSI_EXPORT BinderBuffer : public facebook::jsi::Buffer {
public:
    BinderBuffer(std::shared_ptr<IJSIBufferInterface> jsiBufferInterface) : jsiBufferInterface_(jsiBufferInterface) {
        jsiBufferInterface_->data(&vec_);
        vec_.push_back('\0'); // Hack ..

        jsiBufferInterface_->size(&size_);
    }
    size_t size() const override {
        return size_;
    }
    const uint8_t* data() const override {
        return reinterpret_cast<const uint8_t*>(vec_.data());
    }

private:
    std::shared_ptr<IJSIBufferInterface> jsiBufferInterface_;
    std::vector<int8_t> vec_;
    int64_t size_;
};

JSIService::JSIService(std::shared_ptr<IRemoteJSIInterface> remoteJsiInterface) : remoteJsiInterface_(remoteJsiInterface) {
    bool isRemote = this->isRemote();
    runtime_ = facebook::hermes::makeHermesRuntime();
}

::ndk::ScopedAStatus JSIService::eval(const ::ndk::SpAIBinder& in_bufferBinder, const std::string& in_sourceURL,::ndk::SpAIBinder* _aidl_return) {
    auto jsiBufferService = IJSIBufferInterface::fromBinder(in_bufferBinder);
    auto script = std::make_shared<BinderBuffer>(jsiBufferService);
    std::string sourceUrl = "MyScript";
    std::string scriptstr((const char*)script->data(), script->size());
    facebook::jsi::Value result = runtime_->evaluateJavaScript(script, sourceUrl);

    auto jsiValueService = ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::JSIValueService>(runtime_, std::move(result));
    *_aidl_return = jsiValueService->asBinder();

    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIService::cloneValue(int8_t in_valueType, bool in_boolValue, double in_doubleValue, const ::ndk::SpAIBinder& in_pointerBinder, ::ndk::SpAIBinder* _aidl_return) {
    facebook::jsi::Value resultJSValue;
    switch (in_valueType) {
        case 0:
            resultJSValue = facebook::jsi::Value::undefined();
            LOGE("[App] [cpp] Successfully retrieved result from binder: <undefined>");
            break;
        case 1:
            resultJSValue = facebook::jsi::Value::null();
            LOGE("[App] [cpp] Successfully retrieved result from binder: <null>");
            break;
        case 2:
            resultJSValue = facebook::jsi::Value(in_boolValue);
            LOGE("[App] [cpp] Successfully retrieved result from binder: %s",
                 in_boolValue ? "true" : "false");
            break;
        case 3:
            resultJSValue = facebook::jsi::Value(in_doubleValue);
            LOGE("[App] [cpp] Successfully retrieved result from binder: %d", in_doubleValue);
            break;
        case 4: {
            auto jsiSymbolService = aidl::com::example::remotejsi::JSISymbolService::fromBinder(
                    in_pointerBinder);
            JSISymbolService *symbolService = static_cast<JSISymbolService *>(jsiSymbolService.get());
            resultJSValue = facebook::jsi::Value(symbolService->copySymbol());
            LOGE("[App] [cpp] Successfully retrieved symbol from binder");
        }
            break;
        case 5: {
            auto jsiStringService = aidl::com::example::remotejsi::JSIStringService::fromBinder(
                    in_pointerBinder);
            JSIStringService *stringService = static_cast<JSIStringService *>(jsiStringService.get());
            resultJSValue = facebook::jsi::Value(stringService->copyString());
            LOGE("[App] [cpp] Successfully retrieved string from binder");
        }
            break;
        case 6: {
            auto jsiObjectService = aidl::com::example::remotejsi::JSIObjectService::fromBinder(
                    in_pointerBinder);
            JSIObjectService *objectService = static_cast<JSIObjectService *>(jsiObjectService.get());
            resultJSValue = facebook::jsi::Value(objectService->copyObject());
            LOGE("[App] [cpp] Successfully retrieved object from binder");
        }
        default:
            std::abort();
            break;
    }

    *_aidl_return = ::ndk::SharedRefBase::make<JSIValueService>(runtime_, std::move(resultJSValue))->asBinder();
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIService::createObject(::ndk::SpAIBinder* _aidl_return) {
    facebook::jsi::Object obj(*runtime_);
    *_aidl_return = ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::JSIObjectService>(runtime_, std::move(obj))->asBinder();
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIService::createFromAscii(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) {
    const char* chars = reinterpret_cast<const char* >(const_cast<signed char*>(in_chars.data()));
    facebook::jsi::String str = facebook::jsi::String::createFromAscii(*runtime_, chars, in_length);
    *_aidl_return = ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::JSIStringService>(runtime_, std::move(str))->asBinder();
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIService::createFromUtf8(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) {
    const uint8_t* chars = reinterpret_cast<const uint8_t* >(const_cast<signed char*>(in_chars.data()));
    facebook::jsi::String str = facebook::jsi::String::createFromUtf8(*runtime_, chars, in_length);
    *_aidl_return = ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::JSIStringService>(runtime_, std::move(str))->asBinder();
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIService::createValueCollection(::ndk::SpAIBinder* _aidl_return) {
    return ::ndk::ScopedAStatus::ok();
}

}
