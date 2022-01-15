//
// Created by anandrag on 1/12/2022.
//

#include <android/binder_ibinder_jni.h>
#include "JSIService.h"
#include "RemoteJSIService.h"
#include "JSIBufferService.h"
#include "JSIValueService.h"

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
    LOGD("Evaluating script");
    std::string scriptstr((const char*)script->data(), script->size());
    LOGD("Evaluating %s", scriptstr.c_str());
    // facebook::jsi::Value result = runtime_->evaluateJavaScript(std::make_shared<StringBuffer>(scriptstr), sourceUrl);
    facebook::jsi::Value result = runtime_->evaluateJavaScript(script, sourceUrl);
/*    LOGD("Done evaluation");
    if(result.isString()) {
        facebook::jsi::String stringRes = result.getString(*runtime_);
        *_aidl_return = stringRes.utf8(*runtime_);
    } else {
        *_aidl_return = std::string("non-string return value from script evaluation");
    }*/

    auto jsiValueService = ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::JSIValueService>(runtime_, std::move(result));
    *_aidl_return = jsiValueService->asBinder();

    return ::ndk::ScopedAStatus::ok();
}

}
