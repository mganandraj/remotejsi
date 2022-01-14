//
// Created by anandrag on 1/12/2022.
//

#ifndef REMOTEJSI_JSISERVICE_H
#define REMOTEJSI_JSISERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIInterface.h>

#include <aidl/com/example/remotejsi/BpRemoteJSIInterface.h>

#include <hermes/hermes.h>

namespace aidl::com::example::remotejsi {
class JSIService : public BnJSIInterface {
public:
    JSIService(std::shared_ptr<IRemoteJSIInterface> remoteJsiInterface);
    ::ndk::ScopedAStatus eval(const std::string& in_aString, std::string* _aidl_return) override;

private:
    std::unique_ptr<facebook::hermes::HermesRuntime> runtime_;
    std::shared_ptr<IRemoteJSIInterface> remoteJsiInterface_;
};
}

#endif //REMOTEJSI_JSISERVICE_H
