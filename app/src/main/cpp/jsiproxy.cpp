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

void checkValue(facebook::jsi::Runtime& runtime, facebook::jsi::Value& value) {
    if(value.isString()) {
        facebook::jsi::String str = value.getString(runtime);
        LOGD("Received String result: %s", str.utf8(runtime).c_str());
    } else if(value.isObject()) {
        facebook::jsi::Object obj = value.getObject(runtime);
        LOGD("Received String result: %d props", obj.getPropertyNames(runtime).size(runtime));
    } else if(value.isSymbol()) {
        facebook::jsi::Symbol sym = value.getSymbol(runtime);
        LOGD("Received Symbol result");
    } else if(value.isNumber()) {
        LOGD("Received Number result: %d", value.getNumber());
    } else if(value.isBool()) {
        bool resbool = value.getBool();
        LOGD("Received Bool result: %d", resbool ? "<true>" : "<false>");
    } else if(value.isNull()) {
        LOGD("Received Bool result: <null>");
    } else if(value.isUndefined()) {
        LOGD("Received Bool result: <undefined>");
    } else {
        LOGE("Unknown result !!");
    }
}

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
        // facebook::jsi::Value result = jsiRuntime->evaluateJavaScript(script, sourceUrl);
        // checkValue(*jsiRuntime, result);

        facebook::jsi::Object object(*jsiRuntime);
        object.setProperty(*jsiRuntime, "name", "anand");
        facebook::jsi::Value resSet = object.getProperty(*jsiRuntime, "name");
        checkValue(*jsiRuntime, resSet);

        auto hostFunction = [](facebook::jsi::Runtime& rt, const facebook::jsi::Value& thisVal, const facebook::jsi::Value* args, size_t count) -> facebook::jsi::Value {
            LOGD("Host Function callback");
        };

        facebook::jsi::Object hostFunc= facebook::jsi::Function::createFromHostFunction(*jsiRuntime, facebook::jsi::PropNameID::forAscii(*jsiRuntime, "hostfunc"), 0, std::move(hostFunction));
        facebook::jsi::Object global = jsiRuntime->global();
        global.setProperty(*jsiRuntime, facebook::jsi::PropNameID::forAscii(*jsiRuntime, "hostfunc"), hostFunc);
    }

    std::string sRet("Succeess");
    return env->NewStringUTF(sRet.c_str());
}