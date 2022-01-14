//
// Created by anandrag on 1/12/2022.
//

#include <android/binder_ibinder_jni.h>
#include "JSIService.h"
#include "RemoteJSIService.h"

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

namespace aidl::com::example::remotejsi {

JSIService::JSIService(std::shared_ptr<IRemoteJSIInterface> remoteJsiInterface) : remoteJsiInterface_(remoteJsiInterface) {
    bool isRemote = this->isRemote();
    runtime_ = facebook::hermes::makeHermesRuntime();
}

::ndk::ScopedAStatus JSIService::eval(const std::string& in_aString, std::string* _aidl_return) {
    bool isRemote = this->isRemote();

    auto script = std::make_shared<StringBuffer>(in_aString);
    std::string sourceUrl = "MyScript";
    facebook::jsi::Value result = runtime_->evaluateJavaScript(script, sourceUrl);
    if(result.isString()) {
        facebook::jsi::String stringRes = result.getString(*runtime_);
        *_aidl_return = stringRes.utf8(*runtime_);
    } else {
        *_aidl_return = std::string("non-string return value from script evaluation");
    }

    return ::ndk::ScopedAStatus::ok();
}

}
