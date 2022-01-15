//
// Created by anandrag on 1/15/2022.
//

#ifndef REMOTEJSI_JSIVALUESERVICE_H
#define REMOTEJSI_JSIVALUESERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIValueInterface.h>

#include <hermes/hermes.h>

namespace aidl::com::example::remotejsi {
class JSIValueService : public BnJSIValueInterface {
public:
    JSIValueService(std::shared_ptr<facebook::jsi::Runtime> runtime, facebook::jsi::Value jsValue);

    ::ndk::ScopedAStatus getType(int8_t* _aidl_return) override;
    ::ndk::ScopedAStatus getNumber(double* _aidl_return) override;
    ::ndk::ScopedAStatus getBoolean(bool* _aidl_return) override;
    ::ndk::ScopedAStatus getString(::ndk::SpAIBinder* _aidl_return) override;
    ::ndk::ScopedAStatus getObject(::ndk::SpAIBinder* _aidl_return) override;
    ::ndk::ScopedAStatus getSymbol(::ndk::SpAIBinder* _aidl_return) override;

private:
    std::shared_ptr<facebook::jsi::Runtime> runtime_;
    facebook::jsi::Value jsValue_;
};
}

#endif //REMOTEJSI_JSIVALUESERVICE_H
