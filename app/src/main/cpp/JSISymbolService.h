//
// Created by anandrag on 1/15/2022.
//

#ifndef REMOTEJSI_JSISYMBOLSERVICE_H
#define REMOTEJSI_JSISYMBOLSERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSISymbolInterface.h>

#include <hermes/hermes.h>

namespace aidl::com::example::remotejsi {
    class JSISymbolService : public BnJSISymbolInterface {
    public:
        JSISymbolService(std::shared_ptr<facebook::jsi::Runtime> runtime, facebook::jsi::Symbol jsSymbol);
    public:
        facebook::jsi::Symbol copySymbol();
    private:
        std::shared_ptr<facebook::jsi::Runtime> runtime_;
        facebook::jsi::Symbol jsSymbol_;
    };
}

#endif //REMOTEJSI_JSISYMBOLSERVICE_H
