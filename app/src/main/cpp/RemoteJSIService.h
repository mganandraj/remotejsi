//
// Created by anandrag on 1/13/2022.
//

#ifndef REMOTEJSI_REMOTEJSISERVICE_H
#define REMOTEJSI_REMOTEJSISERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnRemoteJSIInterface.h>

namespace aidl::com::example::remotejsi {
class RemoteJSIService : public BnRemoteJSIInterface
{
public:
    // ::ndk::ScopedAStatus basicTypes(int32_t in_anInt, int64_t in_aLong, bool in_aBoolean, float in_aFloat, double in_aDouble, const std::string& in_aString) override;
    ::ndk::ScopedAStatus handshakeAck() override;
};
}

#endif //REMOTEJSI_REMOTEJSISERVICE_H
