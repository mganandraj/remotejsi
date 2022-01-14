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
    ::ndk::ScopedAStatus handshakeAck() override;
};
}

#endif //REMOTEJSI_REMOTEJSISERVICE_H
