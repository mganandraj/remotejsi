//
// Created by anandrag on 1/17/2022.
//

#ifndef REMOTEJSI_JSIVALUECOLLECTIONSERVICE_H
#define REMOTEJSI_JSIVALUECOLLECTIONSERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnValueCollectionInterface.h>

#include <hermes/hermes.h>

namespace aidl::com::example::remotejsi {

    class JSIValueCollectionService : public BnValueCollectionInterface {
    public:
        JSIValueCollectionService(std::shared_ptr<facebook::jsi::Runtime> runtime);

        ::ndk::ScopedAStatus add(const ::ndk::SpAIBinder& in_value) override;
        ::ndk::ScopedAStatus get(int64_t in_index, ::ndk::SpAIBinder* _aidl_return) override;
        ::ndk::ScopedAStatus getCount(int64_t* _aidl_return) override;

    private:
        std::shared_ptr<facebook::jsi::Runtime> runtime_;
        std::vector<facebook::jsi::Value> jsValues_;
    };
}
#endif //REMOTEJSI_JSIVALUECOLLECTIONSERVICE_H
