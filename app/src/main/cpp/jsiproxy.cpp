#include <jni.h>
#include <string>
#include <set>

#include <stdlib.h>

#include "JSIService.h"
#include "RemoteJSIService.h"
#include "ManagerService.h"

#include <android/binder_ibinder_jni.h>

#define LOG_TAG "remotejsi-native-lib"
#include "logging.h"

#include "JSIProxyRuntime.h"

using namespace aidl::com::example::remotejsi;
using namespace std;

#include <aidl/com/example/remotejsi/BpManagerInterface.h>
std::shared_ptr<IManagerInterface> g_spManagerService;

extern "C" JNIEXPORT void JNICALL
Java_com_example_remotejsi_JSIProxy_onServiceConnected(
        JNIEnv* env,
        jobject /* this */,
        jobject binder)
{
    g_spManagerService = IManagerInterface::fromBinder(::ndk::SpAIBinder(AIBinder_fromJavaBinder(env, binder)));
    LOGD("[App] [cpp] onServiceConnected");
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_remotejsi_JSIProxy_onServiceDisconnected(
        JNIEnv* env,
        jobject /* this */)
{
    g_spManagerService = nullptr;
    LOGD("[App] [cpp] onServiceDisconnected");
}

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

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_remotejsi_JSIProxy_talkToService(
        JNIEnv* env,
        jobject /* this */)
{
    ::ndk::ScopedAStatus pingResult = g_spManagerService->ping();
    if(pingResult.isOk())
    {
        LOGD("[App] [cpp] IMyService.ping - Succeeded");
    }
    else
    {
        LOGE("[App] [cpp] IMyService.ping - Failed");
    }

    {
        std::unique_ptr<facebook::jsi::Runtime> jsiRuntime = com::example::remotejsi::makeJSIProxyRuntime(g_spManagerService);
        auto script = std::make_shared<StringBuffer>("\"abcde\"");
        std::string sourceUrl = "MyScript";
        facebook::jsi::Value result = jsiRuntime->evaluateJavaScript(script, sourceUrl);
        if(result.isString()) {
            facebook::jsi::String str = result.getString(*jsiRuntime);
            LOGD("Received String result: %s", str.utf8(*jsiRuntime).c_str());
        } else if(result.isObject()) {
            facebook::jsi::Object obj = result.getObject(*jsiRuntime);
            LOGD("Received String result: %d props", obj.getPropertyNames(*jsiRuntime).size(*jsiRuntime));
        } else if(result.isSymbol()) {
            facebook::jsi::Symbol sym = result.getSymbol(*jsiRuntime);
            LOGD("Received Symbol result");
        } else if(result.isNumber()) {
            LOGD("Received Number result: %d", result.getNumber());
        } else if(result.isBool()) {
            bool resbool = result.getBool();
            LOGD("Received Bool result: %d", resbool ? "<true>" : "<false>");
        } else if(result.isNull()) {
            LOGD("Received Bool result: <null>");
        } else if(result.isUndefined()) {
            LOGD("Received Bool result: <undefined>");
        } else {
            LOGE("Unknown result !!");
        }
    }

    std::string sRet("Succeess");
    return env->NewStringUTF(sRet.c_str());
}