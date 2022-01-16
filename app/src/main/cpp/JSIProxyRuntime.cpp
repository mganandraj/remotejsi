//
// Created by anandrag on 1/14/2022.
//

/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "JSIProxyRuntime.h"

#include <jsi/jsilib.h>
#include <array>
#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <mutex>
#include <queue>
#include <sstream>
#include <thread>

#include "JSIService.h"
#include "RemoteJSIService.h"
#include "ManagerService.h"
#include "JSIBufferService.h"
#include "JSIValueService.h"
#include "JSIStringService.h"
#include "JSIObjectService.h"
#include "JSISymbolService.h"

#define LOG_TAG "JSIProxyRuntime"
#include "logging.h"


using namespace facebook;
namespace com::example::remotejsi {

        /*namespace detail {
            class ArgsConverter;
        } // namespace detail

        struct Lock {
            void lock(const JSIProxy::JSIProxyRuntime &) const {}
            void unlock(const JSIProxy::JSIProxyRuntime &) const {}
        };*/

class JSIProxyRuntime : public jsi::Runtime {
public:
    // Creates new context in new context group
    JSIProxyRuntime(std::shared_ptr<aidl::com::example::remotejsi::IManagerInterface> managerService);
    // Retains ctx
    // JSIProxyRuntime(JSGlobalContextRef ctx);

    std::shared_ptr<const jsi::PreparedJavaScript> prepareJavaScript(
            const std::shared_ptr<const jsi::Buffer> &buffer,
            std::string sourceURL) override;

    jsi::Value evaluatePreparedJavaScript(
            const std::shared_ptr<const jsi::PreparedJavaScript> &js) override;

    jsi::Value evaluateJavaScript(
            const std::shared_ptr<const jsi::Buffer> &buffer,
            const std::string &sourceURL) override;
    jsi::Object global() override;

    bool drainMicrotasks(int maxMicrotasksHint = -1) override;


    std::string description() override;

    bool isInspectable() override;

    void setDescription(const std::string &desc);

    jsi::Value createValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIValueInterface> value) const;

    std::shared_ptr<aidl::com::example::remotejsi::IJSIValueInterface> valueRef(const jsi::Value &value);

    jsi::String createStringValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> value) const;
    jsi::Object createObjectValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> value) const;
    jsi::Symbol createSymbolValue(std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> value) const;
    jsi::PropNameID createPropNameID(std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> value) const;

    // Used by factory methods and clone methods
    jsi::Runtime::PointerValue *makeSymbolValue(std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> value) const;
    jsi::Runtime::PointerValue *makeStringValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> value) const;
    jsi::Runtime::PointerValue *makeObjectValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> value) const;


protected:
    // friend class detail::ArgsConverter;
    class JSIProxySymbolValue final : public PointerValue {
#ifndef NDEBUG
        JSIProxySymbolValue(std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> sym
        , std::atomic<intptr_t> &counter);
#else
        JSIProxySymbolValue(std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> sym);
#endif
        void invalidate() override;

    protected:
        friend class JSIProxyRuntime;

    private:
#ifndef NDEBUG
        std::atomic<intptr_t> &counter_;
#endif
        std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> sym_;
    };

    class JSIProxyStringValue final : public PointerValue {
#ifndef NDEBUG
        JSIProxyStringValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> str
                , std::atomic<intptr_t> &counter);
#else
        JSIProxyStringValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> str);
#endif
        void invalidate() override;

    protected:
        friend class JSIProxyRuntime;
    private:
#ifndef NDEBUG
        std::atomic<intptr_t> &counter_;
#endif
        std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> str_;
    };

    class JSIProxyObjectValue final : public PointerValue {
#ifndef NDEBUG
        JSIProxyObjectValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> obj
                , std::atomic<intptr_t> &counter);
#else
        JSIProxyObjectValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> obj);
#endif
        void invalidate() override;
    protected:
        friend class JSIProxyRuntime;
    private:
#ifndef NDEBUG
        std::atomic<intptr_t> &counter_;
#endif
        std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> obj_;
    };

    PointerValue *cloneSymbol(const Runtime::PointerValue *pv) override;
    PointerValue *cloneString(const Runtime::PointerValue *pv) override;
    PointerValue *cloneObject(const Runtime::PointerValue *pv) override;
    PointerValue *clonePropNameID(const Runtime::PointerValue *pv) override;

    jsi::PropNameID createPropNameIDFromAscii(const char *str, size_t length)
    override;
    jsi::PropNameID createPropNameIDFromUtf8(const uint8_t *utf8, size_t length)
    override;
    jsi::PropNameID createPropNameIDFromString(const jsi::String &str) override;
    std::string utf8(const jsi::PropNameID &) override;
    bool compare(const jsi::PropNameID &, const jsi::PropNameID &) override;

    std::string symbolToString(const jsi::Symbol &) override;

    jsi::String createStringFromAscii(const char *str, size_t length) override;
    jsi::String createStringFromUtf8(const uint8_t *utf8, size_t length) override;
    std::string utf8(const jsi::String &) override;

    jsi::Object createObject() override;
    jsi::Object createObject(std::shared_ptr<jsi::HostObject> ho) override;
    virtual std::shared_ptr<jsi::HostObject> getHostObject(
            const jsi::Object &) override;
    jsi::HostFunctionType &getHostFunction(const jsi::Function &) override;

    jsi::Value getProperty(const jsi::Object &, const jsi::String &name) override;
    jsi::Value getProperty(const jsi::Object &, const jsi::PropNameID &name)
    override;
    bool hasProperty(const jsi::Object &, const jsi::String &name) override;
    bool hasProperty(const jsi::Object &, const jsi::PropNameID &name) override;
    void setPropertyValue(
            jsi::Object &,
            const jsi::String &name,
            const jsi::Value &value) override;
    void setPropertyValue(
            jsi::Object &,
            const jsi::PropNameID &name,
            const jsi::Value &value) override;
    bool isArray(const jsi::Object &) const override;
    bool isArrayBuffer(const jsi::Object &) const override;
    bool isFunction(const jsi::Object &) const override;
    bool isHostObject(const jsi::Object &) const override;
    bool isHostFunction(const jsi::Function &) const override;
    jsi::Array getPropertyNames(const jsi::Object &) override;

    // TODO: revisit this implementation
    jsi::WeakObject createWeakObject(const jsi::Object &) override;
    jsi::Value lockWeakObject(jsi::WeakObject &) override;

    jsi::Array createArray(size_t length) override;
    size_t size(const jsi::Array &) override;
    size_t size(const jsi::ArrayBuffer &) override;
    uint8_t *data(const jsi::ArrayBuffer &) override;
    jsi::Value getValueAtIndex(const jsi::Array &, size_t i) override;
    void setValueAtIndexImpl(jsi::Array &, size_t i, const jsi::Value &value)
    override;

    jsi::Function createFunctionFromHostFunction(
            const jsi::PropNameID &name,
            unsigned int paramCount,
            jsi::HostFunctionType func) override;
    jsi::Value call(
            const jsi::Function &,
            const jsi::Value &jsThis,
            const jsi::Value *args,
            size_t count) override;
    jsi::Value callAsConstructor(
            const jsi::Function &,
            const jsi::Value *args,
            size_t count) override;

    bool strictEquals(const jsi::Symbol &a, const jsi::Symbol &b) const override;
    bool strictEquals(const jsi::String &a, const jsi::String &b) const override;
    bool strictEquals(const jsi::Object &a, const jsi::Object &b) const override;
    bool instanceOf(const jsi::Object &o, const jsi::Function &f) override;

private:
    // Basically convenience casts
    static std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> symbolRef(const jsi::Symbol &str);
    static std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> stringRef(const jsi::String &str);
    static std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> stringRef(const jsi::PropNameID &sym);
    static std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> objectRef(const jsi::Object &obj);

    ::ndk::SpAIBinder getValueBinder(const jsi::Value& value);

//#ifdef RN_FABRIC_ENABLED
//            static JSObjectRef objectRef(const jsi::WeakObject &obj);
//#endif

    // Factory methods for creating String/Object
    /*jsi::Symbol createSymbol(JSValueRef symbolRef) const;
    jsi::String createString(JSStringRef stringRef) const;
    jsi::PropNameID createPropNameID(JSStringRef stringRef);
    jsi::Object createObject(JSObjectRef objectRef) const;*/

    // Used by factory methods and clone methods
    /*jsi::Runtime::PointerValue *makeSymbolValue(JSValueRef sym) const;
    jsi::Runtime::PointerValue *makeStringValue(JSStringRef str) const;
    jsi::Runtime::PointerValue *makeObjectValue(JSObjectRef obj) const;

    void checkException(JSValueRef exc);
    void checkException(JSValueRef res, JSValueRef exc);
    void checkException(JSValueRef exc, const char *msg);
    void checkException(JSValueRef res, JSValueRef exc, const char *msg);

    JSGlobalContextRef ctx_;*/
    std::atomic<bool> ctxInvalid_;
    std::string desc_;
#ifndef NDEBUG
    mutable std::atomic<intptr_t> objectCounter_;
    mutable std::atomic<intptr_t> symbolCounter_;
    mutable std::atomic<intptr_t> stringCounter_;
#endif

    std::shared_ptr<aidl::com::example::remotejsi::RemoteJSIService> remoteJSIService_;
    std::shared_ptr<aidl::com::example::remotejsi::IManagerInterface> managerService_;

    std::shared_ptr<aidl::com::example::remotejsi::IJSIInterface> jsiService_;
};

#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

#if __has_builtin(__builtin_expect) || defined(__GNUC__)
        #define JSIProxy_LIKELY(EXPR) __builtin_expect((bool)(EXPR), true)
#define JSIProxy_UNLIKELY(EXPR) __builtin_expect((bool)(EXPR), false)
#else
#define JSIProxy_LIKELY(EXPR) (EXPR)
#define JSIProxy_UNLIKELY(EXPR) (EXPR)
#endif

#define JSIProxy_ASSERT(x)          \
  do {                         \
    if (JSIProxy_UNLIKELY(!!(x))) { \
      abort();                 \
    }                          \
  } while (0)

#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
        // This takes care of watch and tvos (due to backwards compatibility in
// Availability.h
#if __IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_9_0
#define _JSIProxy_FAST_IS_ARRAY
#endif
#if __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_10_0
#define _JSIProxy_NO_ARRAY_BUFFERS
#endif
#endif
#if defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
        #if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_10_11
// Only one of these should be set for a build.  If somehow that's not
// true, this will be a compile-time error and it can be resolved when
// we understand why.
#define _JSIProxy_FAST_IS_ARRAY
#endif
#if __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_10_12
#define _JSIProxy_NO_ARRAY_BUFFERS
#endif
#endif

// std::string utility
namespace {
    std::string to_string(void *value) {
        std::ostringstream ss;
        ss << value;
        return ss.str();
    }
} // namespace

JSIProxyRuntime::JSIProxyRuntime(std::shared_ptr<aidl::com::example::remotejsi::IManagerInterface> managerService) : managerService_(managerService) {
    remoteJSIService_ =  ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::RemoteJSIService>();

    ::ndk::SpAIBinder jsiServiceBinder;
    ::ndk::ScopedAStatus createJSIResult = managerService_->createJSIInterface(
            remoteJSIService_->asBinder(), &jsiServiceBinder);
    jsiService_ = aidl::com::example::remotejsi::IJSIInterface::fromBinder(jsiServiceBinder);
    if (createJSIResult.isOk()) {
        LOGD("[App] [cpp] IMyService.createJSI - Succeeded");
    } else {
        LOGE("[App] [cpp] IMyService.createJSI - Failed");
    }
}

std::shared_ptr<const jsi::PreparedJavaScript> JSIProxyRuntime::prepareJavaScript(
        const std::shared_ptr<const jsi::Buffer> &buffer,
        std::string sourceURL) {
    return nullptr;
}

jsi::Value JSIProxyRuntime::evaluatePreparedJavaScript(
        const std::shared_ptr<const jsi::PreparedJavaScript> &js) {
    return jsi::Value::undefined();
}

jsi::Runtime::PointerValue *JSIProxyRuntime::makeSymbolValue(std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> value) const {
#ifndef NDEBUG
    return new JSIProxySymbolValue(value, symbolCounter_);
#else
    return new JSIProxySymbolValue(value);
#endif
}

jsi::Runtime::PointerValue *JSIProxyRuntime::makeStringValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> value) const {
    // TODO Make sure binder is valid
#ifndef NDEBUG
    return new JSIProxyStringValue(value, stringCounter_);
#else
    return new JSIProxyStringValue(value);
#endif
}

jsi::Runtime::PointerValue *JSIProxyRuntime::makeObjectValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> value) const {
#ifndef NDEBUG
    return new JSIProxyObjectValue(value, objectCounter_);
#else
    return new JSIProxyObjectValue(value);
#endif
}

jsi::String JSIProxyRuntime::createStringValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> value) const {
    return make<jsi::String>(makeStringValue(value));
}

jsi::Object JSIProxyRuntime::createObjectValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> value) const {
    return make<jsi::Object>(makeObjectValue(value));
}

jsi::Symbol JSIProxyRuntime::createSymbolValue(std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> value) const {
    return make<jsi::Symbol>(makeSymbolValue(value));
}

jsi::PropNameID JSIProxyRuntime::createPropNameID(std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> value) const {
    return make<jsi::PropNameID>(makeStringValue(value));
}

jsi::Value JSIProxyRuntime::createValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIValueInterface> jsiValueService) const {
    int8_t jsiValueType;
    jsiValueService->getType(&jsiValueType);

    // Undefined: 0
    // Null: 1
    // Boolean: 2
    // Number: 3
    // Symbol: 4
    // String: 5
    // Object: 6

    jsi::Value resultJSValue;
    switch (jsiValueType) {
        case 0:
            resultJSValue = jsi::Value::undefined();
            LOGE("[App] [cpp] Successfully retrieved result from binder: <undefined>");
            break;
        case 1:
            resultJSValue = jsi::Value::null();
            LOGE("[App] [cpp] Successfully retrieved result from binder: <null>");
            break;
        case 2:
            bool resultBool;
            jsiValueService->getBoolean(&resultBool);
            LOGE("[App] [cpp] Successfully retrieved result from binder: %s", resultBool? "true" : "false");
            resultJSValue = jsi::Value(resultBool);
            break;
        case 3:
            double resultDouble;
            jsiValueService->getNumber(&resultDouble);
            LOGE("[App] [cpp] Successfully retrieved result from binder: %d", resultDouble);
            resultJSValue = jsi::Value(resultDouble);
            break;
        case 4: {
            ::ndk::SpAIBinder resultSymbolBinder;
            jsiValueService->getSymbol(&resultSymbolBinder);
            LOGE("[App] [cpp] Successfully retrieved symbol from binder");
            auto jsiSymbolService = aidl::com::example::remotejsi::JSISymbolService::fromBinder(resultSymbolBinder);
            resultJSValue = createSymbolValue(jsiSymbolService);
        }
            break;
        case 5: {
            ::ndk::SpAIBinder resultStringBinder;
            jsiValueService->getString(&resultStringBinder);
            auto jsiStringService = aidl::com::example::remotejsi::JSIStringService::fromBinder(resultStringBinder);
            LOGE("[App] [cpp] Successfully retrieved string from binder");
            resultJSValue = createStringValue(jsiStringService);
        }
            break;
        case 6: {
            ::ndk::SpAIBinder resultObjectBinder;
            jsiValueService->getObject(&resultObjectBinder);
            LOGE("[App] [cpp] Successfully retrieved object from binder");
            auto jsiObjectService = aidl::com::example::remotejsi::JSIObjectService::fromBinder(resultObjectBinder);
            resultJSValue = createObjectValue(jsiObjectService);
        }
            break;
    }

    return resultJSValue;
}

jsi::Value JSIProxyRuntime::evaluateJavaScript(
        const std::shared_ptr<const jsi::Buffer> &buffer,
        const std::string &sourceURL) {
    auto jsiBufferService = ::ndk::SharedRefBase::make<aidl::com::example::remotejsi::JSIBufferService>(std::move(buffer));
    ::ndk::SpAIBinder resultBinder;
    jsiService_->eval(jsiBufferService->asBinder(), sourceURL, &resultBinder);
    return createValue(aidl::com::example::remotejsi::JSIValueService::fromBinder(resultBinder));
}

jsi::Object JSIProxyRuntime::global() {
    return jsi::Value::null().asObject(*this);
}

bool JSIProxyRuntime::drainMicrotasks(int maxMicrotasksHint) {
    return true;
}

std::string JSIProxyRuntime::description() {
    if (desc_.empty()) {
        desc_ = std::string("<JSIProxyRuntime@") + to_string(this) + ">";
    }
    return desc_;
}

bool JSIProxyRuntime::isInspectable() {
    return false;
}

#ifndef NDEBUG
JSIProxyRuntime::JSIProxySymbolValue::JSIProxySymbolValue(
        std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> sym
            ,std::atomic<intptr_t> &counter): sym_(sym), counter_(counter) {
    counter_ += 1;
}
#else
    JSIProxyRuntime::JSIProxySymbolValue::JSIProxySymbolValue(
        std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> sym) {}

#endif

void JSIProxyRuntime::JSIProxySymbolValue::invalidate() {
    delete this;
}

#ifndef NDEBUG
        JSIProxyRuntime::JSIProxyStringValue::JSIProxyStringValue(
            std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> str,
            std::atomic<intptr_t> &counter)
            : str_(str), counter_(counter) {
                counter_ += 1;
        }
#else
        JSIProxyRuntime::JSIProxyStringValue::JSIProxyStringValue(JSStringRef str)
            : str_(str) {}
#endif

void JSIProxyRuntime::JSIProxyStringValue::invalidate() {
    delete this;
}


#ifndef NDEBUG
    JSIProxyRuntime::JSIProxyObjectValue::JSIProxyObjectValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> obj
        , std::atomic<intptr_t> &counter):obj_(obj), counter_(counter) {counter_ += 1;}
#else
    JSIProxyRuntime::JSIProxyObjectValue::JSIProxyObjectValue(std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> obj)
        :obj_(obj) {}
#endif

void JSIProxyRuntime::JSIProxyObjectValue::invalidate() {
    delete this;
}

jsi::Runtime::PointerValue *JSIProxyRuntime::cloneSymbol(
        const jsi::Runtime::PointerValue *pv) {
            if (!pv) {
                return nullptr;
            }
            const JSIProxySymbolValue *symbol = static_cast<const JSIProxySymbolValue *>(pv);
            return makeSymbolValue(symbol->sym_);
}

jsi::Runtime::PointerValue *JSIProxyRuntime::cloneString(
        const jsi::Runtime::PointerValue *pv) {
            if (!pv) {
                return nullptr;
            }
            const JSIProxyStringValue *string = static_cast<const JSIProxyStringValue *>(pv);
            return makeStringValue(string->str_);
}

jsi::Runtime::PointerValue *JSIProxyRuntime::cloneObject(
        const jsi::Runtime::PointerValue *pv) {
            if (!pv) {
                return nullptr;
            }
            const JSIProxyObjectValue *object = static_cast<const JSIProxyObjectValue *>(pv);
            return makeObjectValue(object->obj_);
}

jsi::Runtime::PointerValue *JSIProxyRuntime::clonePropNameID(
        const jsi::Runtime::PointerValue *pv) {
            if (!pv) {
                return nullptr;
            }
            const JSIProxyStringValue *string = static_cast<const JSIProxyStringValue *>(pv);
            return makeStringValue(string->str_);
}

jsi::PropNameID JSIProxyRuntime::createPropNameIDFromAscii(
        const char *str,
        size_t length) {
/*    ::ndk::SpAIBinder resultBinder;
    const std::vector<int8_t> bytes(str, str+length);
    jsiService_->createFromAscii(bytes, length, &resultBinder);
    auto jsiStringService = aidl::com::example::remotejsi::JSIStringService::fromBinder(resultBinder);
    return createPropNameID(jsiStringService);*/
    return createPropNameIDFromUtf8(reinterpret_cast<const uint8_t *>(str), length); // TODO .. Is it correct ?
}

jsi::PropNameID JSIProxyRuntime::createPropNameIDFromUtf8(
        const uint8_t *utf8,
        size_t length) {
    ::ndk::SpAIBinder resultBinder;
    const std::vector<int8_t> bytes(utf8, utf8+length);
    jsiService_->createFromUtf8(bytes, length, &resultBinder);
    auto jsiStringService = aidl::com::example::remotejsi::JSIStringService::fromBinder(resultBinder);
    return createPropNameID(jsiStringService);
}

jsi::PropNameID JSIProxyRuntime::createPropNameIDFromString(const jsi::String &str) {
    const JSIProxyStringValue* pv = reinterpret_cast<const JSIProxyStringValue*>(getPointerValue(str));
    std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> stringBinder = pv->str_;
    return createPropNameID(stringBinder);
}

std::string JSIProxyRuntime::utf8(const jsi::PropNameID &sym) {
//    const JSIProxyStringValue* pv = reinterpret_cast<const JSIProxyStringValue*>(getPointerValue(str));
//    auto stringBinder = pv->str_;
    std::string result;
    stringRef(sym)->utf8(&result);
    return result;
}

bool JSIProxyRuntime::compare(const jsi::PropNameID &a, const jsi::PropNameID &b) {
    // return JSStringIsEqual(stringRef(a), stringRef(b));
    std::abort();
}

std::string JSIProxyRuntime::symbolToString(const jsi::Symbol &sym) {
    // return jsi::Value(*this, sym).toString(*this).utf8(*this);
    std::abort();
}

jsi::String JSIProxyRuntime::createStringFromAscii(const char *str, size_t length) {
    // Yes we end up double casting for semantic reasons (UTF8 contains ASCII,
    // not the other way around)
    return this->createStringFromUtf8(
            reinterpret_cast<const uint8_t *>(str), length);
}

jsi::String JSIProxyRuntime::createStringFromUtf8(
        const uint8_t *str,
        size_t length) {
    ::ndk::SpAIBinder resultBinder;
    const std::vector<int8_t> bytes(str, str+length);
    jsiService_->createFromUtf8(bytes, length, &resultBinder);
    auto jsiStringService = aidl::com::example::remotejsi::JSIStringService::fromBinder(resultBinder);
    return createStringValue(jsiStringService);
}

std::string JSIProxyRuntime::utf8(const jsi::String &str) {
    // const JSIProxyStringValue* pv = reinterpret_cast<const JSIProxyStringValue*>(getPointerValue(str));
    // auto stringBinder = pv->str_;
    std::string result;
    stringRef(str)->utf8(&result);
    return result;
}

jsi::Object JSIProxyRuntime::createObject() {
    ::ndk::SpAIBinder resultBinder;
    jsiService_->createObject(&resultBinder);
    auto jsiObjectService = aidl::com::example::remotejsi::JSIObjectService::fromBinder(resultBinder);
    return createObjectValue(jsiObjectService);
}

//// HostObject details
//        namespace detail {
//            struct HostObjectProxyBase {
//                HostObjectProxyBase(
//                        JSIProxyRuntime &rt,
//                        const std::shared_ptr<jsi::HostObject> &sho)
//                        : runtime(rt), hostObject(sho) {}
//
//                JSIProxyRuntime &runtime;
//                std::shared_ptr<jsi::HostObject> hostObject;
//            };
//        } // namespace detail
//
//        namespace {
//            std::once_flag hostObjectClassOnceFlag;
//            //JSIProxylassRef hostObjectClass{};
//        } // namespace

jsi::Object JSIProxyRuntime::createObject(std::shared_ptr<jsi::HostObject> ho) {
//            struct HostObjectProxy : public detail::HostObjectProxyBase {
//                static JSValueRef getProperty(
//                        JSIProxyontextRef ctx,
//                        JSObjectRef object,
//                        JSStringRef propName,
//                        JSValueRef *exception) {
//                    auto proxy = static_cast<HostObjectProxy *>(JSObjectGetPrivate(object));
//                    auto &rt = proxy->runtime;
//                    jsi::PropNameID sym = rt.createPropNameID(propName);
//                    jsi::Value ret;
//                    try {
//                        ret = proxy->hostObject->get(rt, sym);
//                    } catch (const jsi::JSError &error) {
//                        *exception = rt.valueRef(error.value());
//                        return JSValueMakeUndefined(ctx);
//                    } catch (const std::exception &ex) {
//                        auto excValue =
//                                rt.global()
//                                        .getPropertyAsFunction(rt, "Error")
//                                        .call(
//                                                rt,
//                                                std::string("Exception in HostObject::get(propName:") +
//                                                JSStringToSTLString(propName) + std::string("): ") +
//                                                ex.what());
//                        *exception = rt.valueRef(excValue);
//                        return JSValueMakeUndefined(ctx);
//                    } catch (...) {
//                        auto excValue =
//                                rt.global()
//                                        .getPropertyAsFunction(rt, "Error")
//                                        .call(
//                                                rt,
//                                                std::string("Exception in HostObject::get(propName:") +
//                                                JSStringToSTLString(propName) +
//                                                std::string("): <unknown>"));
//                        *exception = rt.valueRef(excValue);
//                        return JSValueMakeUndefined(ctx);
//                    }
//                    return rt.valueRef(ret);
//                }
//
//#define JSIProxy_UNUSED(x) (void)(x);
//
//                static bool setProperty(
//                        JSIProxyontextRef ctx,
//                        JSObjectRef object,
//                        JSStringRef propName,
//                        JSValueRef value,
//                        JSValueRef *exception) {
//                    JSIProxy_UNUSED(ctx);
//                    auto proxy = static_cast<HostObjectProxy *>(JSObjectGetPrivate(object));
//                    auto &rt = proxy->runtime;
//                    jsi::PropNameID sym = rt.createPropNameID(propName);
//                    try {
//                        proxy->hostObject->set(rt, sym, rt.createValue(value));
//                    } catch (const jsi::JSError &error) {
//                        *exception = rt.valueRef(error.value());
//                        return false;
//                    } catch (const std::exception &ex) {
//                        auto excValue =
//                                rt.global()
//                                        .getPropertyAsFunction(rt, "Error")
//                                        .call(
//                                                rt,
//                                                std::string("Exception in HostObject::set(propName:") +
//                                                JSStringToSTLString(propName) + std::string("): ") +
//                                                ex.what());
//                        *exception = rt.valueRef(excValue);
//                        return false;
//                    } catch (...) {
//                        auto excValue =
//                                rt.global()
//                                        .getPropertyAsFunction(rt, "Error")
//                                        .call(
//                                                rt,
//                                                std::string("Exception in HostObject::set(propName:") +
//                                                JSStringToSTLString(propName) +
//                                                std::string("): <unknown>"));
//                        *exception = rt.valueRef(excValue);
//                        return false;
//                    }
//                    return true;
//                }
//
//                // JSIProxy does not provide means to communicate errors from this callback,
//                // so the error handling strategy is very brutal - we'll just crash
//                // due to noexcept.
//                static void getPropertyNames(
//                        JSIProxyontextRef ctx,
//                        JSObjectRef object,
//                        JSPropertyNameAccumulatorRef propertyNames) noexcept {
//                    JSIProxy_UNUSED(ctx);
//                    auto proxy = static_cast<HostObjectProxy *>(JSObjectGetPrivate(object));
//                    auto &rt = proxy->runtime;
//                    auto names = proxy->hostObject->getPropertyNames(rt);
//                    for (auto &name : names) {
//                        JSPropertyNameAccumulatorAddName(propertyNames, stringRef(name));
//                    }
//                }
//
//#undef JSIProxy_UNUSED
//
//                static void finalize(JSObjectRef obj) {
//                    auto hostObject = static_cast<HostObjectProxy *>(JSObjectGetPrivate(obj));
//                    JSObjectSetPrivate(obj, nullptr);
//                    delete hostObject;
//                }
//
//                using HostObjectProxyBase::HostObjectProxyBase;
//            };
//
//            std::call_once(hostObjectClassOnceFlag, []() {
//                JSIProxylassDefinition hostObjectClassDef = kJSIProxylassDefinitionEmpty;
//                hostObjectClassDef.version = 0;
//                hostObjectClassDef.attributes = kJSIProxylassAttributeNoAutomaticPrototype;
//                hostObjectClassDef.finalize = HostObjectProxy::finalize;
//                hostObjectClassDef.getProperty = HostObjectProxy::getProperty;
//                hostObjectClassDef.setProperty = HostObjectProxy::setProperty;
//                hostObjectClassDef.getPropertyNames = HostObjectProxy::getPropertyNames;
//                hostObjectClass = JSIProxylassCreate(&hostObjectClassDef);
//            });
//
//            JSObjectRef obj =
//                    JSObjectMake(ctx_, hostObjectClass, new HostObjectProxy(*this, ho));
//            return createObject(obj);
}

std::shared_ptr<jsi::HostObject> JSIProxyRuntime::getHostObject(
        const jsi::Object &obj) {
    // We are guaranteed at this point to have isHostObject(obj) == true
    // so the private data should be HostObjectMetadata
//            JSObjectRef object = objectRef(obj);
//            auto metadata =
//                    static_cast<detail::HostObjectProxyBase *>(JSObjectGetPrivate(object));
//            assert(metadata);
//            return metadata->hostObject;
}

jsi::Value JSIProxyRuntime::getProperty(
        const jsi::Object &obj,
        const jsi::String &name) {
            auto objRef = objectRef(obj);
            ::ndk::SpAIBinder result;
            objRef->get(stringRef(name)->asBinder(), &result);
            return createValue(aidl::com::example::remotejsi::JSIValueService::fromBinder(result));
//            JSValueRef exc = nullptr;
//            JSValueRef res = JSObjectGetProperty(ctx_, objRef, stringRef(name), &exc);
//            checkException(exc);
//            return createValue(res);
}

jsi::Value JSIProxyRuntime::getProperty(
        const jsi::Object &obj,
        const jsi::PropNameID &name) {
            auto objRef = objectRef(obj);
            ::ndk::SpAIBinder result;
            objRef->get(stringRef(name)->asBinder(), &result);
            return createValue(aidl::com::example::remotejsi::JSIValueService::fromBinder(result));
//            JSObjectRef objRef = objectRef(obj);
//            JSValueRef exc = nullptr;
//            JSValueRef res = JSObjectGetProperty(ctx_, objRef, stringRef(name), &exc);
//            checkException(exc);
//            return createValue(res);
}

bool JSIProxyRuntime::hasProperty(const jsi::Object &obj, const jsi::String &name) {
//            JSObjectRef objRef = objectRef(obj);
//            return JSObjectHasProperty(ctx_, objRef, stringRef(name));
}

bool JSIProxyRuntime::hasProperty(
        const jsi::Object &obj,
        const jsi::PropNameID &name) {
//            JSObjectRef objRef = objectRef(obj);
//            return JSObjectHasProperty(ctx_, objRef, stringRef(name));
}

::ndk::SpAIBinder JSIProxyRuntime::getValueBinder(const jsi::Value& value) {
    uint8_t type{0};
    if(value.isUndefined())
        type =0;
    else if (value.isNull())
        type = 1;
    else if (value.isBool())
        type = 2;
    else if (value.isNumber())
        type = 3;
    else if (value.isSymbol())
        type = 4;
    else if (value.isString())
        type = 5;
    else if (value.isObject())
        type = 6;
    else
        std::abort();

    ::ndk::SpAIBinder pointerBinder;
    if(value.isString())
        pointerBinder = stringRef(value.getString(*this))->asBinder();
    else if(value.isObject())
        pointerBinder = objectRef(value.getObject(*this))->asBinder();
    else if(value.isSymbol())
        pointerBinder = symbolRef(value.getSymbol(*this))->asBinder();

    ::ndk::SpAIBinder resultBinder;
    auto jsiValueBinder = jsiService_->cloneValue(type, value.isBool() ? value.getBool() : false,
                                                  value.isNumber()? value.getNumber(): 0,
                                                  pointerBinder, &resultBinder);
    return resultBinder;

}

void JSIProxyRuntime::setPropertyValue(
        jsi::Object &object,
        const jsi::PropNameID &name,
        const jsi::Value &value) {
    auto objRef = objectRef(object);
    ::ndk::SpAIBinder valueBinder = getValueBinder(value);
    objRef->set(stringRef(name)->asBinder(), valueBinder);
}

void JSIProxyRuntime::setPropertyValue(
        jsi::Object &object,
        const jsi::String &name,
        const jsi::Value &value) {
    auto objRef = objectRef(object);
    auto prop = stringRef(name)->asBinder();
    ::ndk::SpAIBinder valueBinder = getValueBinder(value);
    objRef->set(prop, valueBinder);
}

bool JSIProxyRuntime::isArray(const jsi::Object &obj) const {
//#if !defined(_JSIProxy_FAST_IS_ARRAY)
//            JSObjectRef global = JSIProxyontextGetGlobalObject(ctx_);
//            JSStringRef arrayString = getArrayString();
//            JSValueRef exc = nullptr;
//            JSValueRef arrayCtorValue =
//                    JSObjectGetProperty(ctx_, global, arrayString, &exc);
//            JSIProxy_ASSERT(exc);
//            JSObjectRef arrayCtor = JSValueToObject(ctx_, arrayCtorValue, &exc);
//            JSIProxy_ASSERT(exc);
//            JSStringRef isArrayString = getIsArrayString();
//            JSValueRef isArrayValue =
//                    JSObjectGetProperty(ctx_, arrayCtor, isArrayString, &exc);
//            JSIProxy_ASSERT(exc);
//            JSObjectRef isArray = JSValueToObject(ctx_, isArrayValue, &exc);
//            JSIProxy_ASSERT(exc);
//            JSValueRef arg = objectRef(obj);
//            JSValueRef result =
//                    JSObjectCallAsFunction(ctx_, isArray, nullptr, 1, &arg, &exc);
//            JSIProxy_ASSERT(exc);
//            return JSValueToBoolean(ctx_, result);
//#else
//            return JSValueIsArray(ctx_, objectRef(obj));
//#endif
}

bool JSIProxyRuntime::isArrayBuffer(const jsi::Object &obj) const {
//#if defined(_JSIProxy_NO_ARRAY_BUFFERS)
//            throw std::runtime_error("Unsupported");
//#else
//            auto typedArrayType = JSValueGetTypedArrayType(ctx_, objectRef(obj), nullptr);
//            return typedArrayType == kJSTypedArrayTypeArrayBuffer;
//#endif
}

uint8_t *JSIProxyRuntime::data(const jsi::ArrayBuffer &obj) {
//#if defined(_JSIProxy_NO_ARRAY_BUFFERS)
//            throw std::runtime_error("Unsupported");
//#else
//            return static_cast<uint8_t *>(
//                    JSObjectGetArrayBufferBytesPtr(ctx_, objectRef(obj), nullptr));
//#endif
}

size_t JSIProxyRuntime::size(const jsi::ArrayBuffer &obj) {
//#if defined(_JSIProxy_NO_ARRAY_BUFFERS)
//            throw std::runtime_error("Unsupported");
//#else
//            return JSObjectGetArrayBufferByteLength(ctx_, objectRef(obj), nullptr);
//#endif
}

bool JSIProxyRuntime::isFunction(const jsi::Object &obj) const {
//            return JSObjectIsFunction(ctx_, objectRef(obj));
}

bool JSIProxyRuntime::isHostObject(const jsi::Object &obj) const {
//            auto cls = hostObjectClass;
//            return cls != nullptr && JSValueIsObjectOfClass(ctx_, objectRef(obj), cls);
}

// Very expensive
jsi::Array JSIProxyRuntime::getPropertyNames(const jsi::Object &obj) {
//            JSPropertyNameArrayRef names =
//                    JSObjectCopyPropertyNames(ctx_, objectRef(obj));
//            size_t len = JSPropertyNameArrayGetCount(names);
//            // Would be better if we could create an array with explicit elements
//            auto result = createArray(len);
//            for (size_t i = 0; i < len; i++) {
//                JSStringRef str = JSPropertyNameArrayGetNameAtIndex(names, i);
//                result.setValueAtIndex(*this, i, createString(str));
//            }
//            JSPropertyNameArrayRelease(names);
//            return result;
}

jsi::WeakObject JSIProxyRuntime::createWeakObject(const jsi::Object &obj) {
//#ifdef RN_FABRIC_ENABLED
//            // TODO: revisit this implementation
//  JSObjectRef objRef = objectRef(obj);
//  return make<jsi::WeakObject>(makeObjectValue(objRef));
//#else
//            throw std::logic_error("Not implemented");
//#endif
}

jsi::Value JSIProxyRuntime::lockWeakObject(jsi::WeakObject &obj) {
//#ifdef RN_FABRIC_ENABLED
//            // TODO: revisit this implementation
//  JSObjectRef objRef = objectRef(obj);
//  return jsi::Value(createObject(objRef));
//#else
//            throw std::logic_error("Not implemented");
//#endif
}

jsi::Array JSIProxyRuntime::createArray(size_t length) {
//            JSValueRef exc = nullptr;
//            JSObjectRef obj = JSObjectMakeArray(ctx_, 0, nullptr, &exc);
//            checkException(obj, exc);
//            JSObjectSetProperty(
//                    ctx_,
//                    obj,
//                    getLengthString(),
//                    JSValueMakeNumber(ctx_, static_cast<double>(length)),
//                    0,
//                    &exc);
//            checkException(exc);
//            return createObject(obj).getArray(*this);
}

size_t JSIProxyRuntime::size(const jsi::Array &arr) {
//            return static_cast<size_t>(
//                    getProperty(arr, createPropNameID(getLengthString())).getNumber());
}

jsi::Value JSIProxyRuntime::getValueAtIndex(const jsi::Array &arr, size_t i) {
//            JSValueRef exc = nullptr;
//            auto res = JSObjectGetPropertyAtIndex(ctx_, objectRef(arr), (int)i, &exc);
//            checkException(exc);
//            return createValue(res);
}

void JSIProxyRuntime::setValueAtIndexImpl(
        jsi::Array &arr,
        size_t i,
        const jsi::Value &value) {
//            JSValueRef exc = nullptr;
//            JSObjectSetPropertyAtIndex(
//                    ctx_, objectRef(arr), (int)i, valueRef(value), &exc);
//            checkException(exc);
}

//        namespace {
//            std::once_flag hostFunctionClassOnceFlag;
//            JSIProxylassRef hostFunctionClass{};
//
//            class HostFunctionProxy {
//            public:
//                HostFunctionProxy(jsi::HostFunctionType hostFunction)
//                        : hostFunction_(hostFunction) {}
//
//                jsi::HostFunctionType &getHostFunction() {
//                    return hostFunction_;
//                }
//
//            protected:
//                jsi::HostFunctionType hostFunction_;
//            };
//        } // namespace

jsi::Function JSIProxyRuntime::createFunctionFromHostFunction(
        const jsi::PropNameID &name,
        unsigned int paramCount,
        jsi::HostFunctionType func) {
//            class HostFunctionMetadata : public HostFunctionProxy {
//            public:
//                static void initialize(JSIProxyontextRef ctx, JSObjectRef object) {
//                    // We need to set up the prototype chain properly here. In theory we
//                    // could set func.prototype.prototype = Function.prototype to get the
//                    // same result. Not sure which approach is better.
//                    HostFunctionMetadata *metadata =
//                            static_cast<HostFunctionMetadata *>(JSObjectGetPrivate(object));
//
//                    JSValueRef exc = nullptr;
//                    JSObjectSetProperty(
//                            ctx,
//                            object,
//                            getLengthString(),
//                            JSValueMakeNumber(ctx, metadata->argCount),
//                            kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontEnum |
//                            kJSPropertyAttributeDontDelete,
//                            &exc);
//                    if (exc) {
//                        // Silently fail to set length
//                        exc = nullptr;
//                    }
//
//                    JSStringRef name = nullptr;
//                    std::swap(metadata->name, name);
//                    JSObjectSetProperty(
//                            ctx,
//                            object,
//                            getNameString(),
//                            JSValueMakeString(ctx, name),
//                            kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontEnum |
//                            kJSPropertyAttributeDontDelete,
//                            &exc);
//                    JSStringRelease(name);
//                    if (exc) {
//                        // Silently fail to set name
//                        exc = nullptr;
//                    }
//
//                    JSObjectRef global = JSIProxyontextGetGlobalObject(ctx);
//                    JSValueRef value =
//                            JSObjectGetProperty(ctx, global, getFunctionString(), &exc);
//                    // If we don't have Function then something bad is going on.
//                    if (JSIProxy_UNLIKELY(exc)) {
//                        abort();
//                    }
//                    JSObjectRef funcCtor = JSValueToObject(ctx, value, &exc);
//                    if (!funcCtor) {
//                        // We can't do anything if Function is not an object
//                        return;
//                    }
//                    JSValueRef funcProto = JSObjectGetPrototype(ctx, funcCtor);
//                    JSObjectSetPrototype(ctx, object, funcProto);
//                }
//
//                static JSValueRef makeError(JSIProxyRuntime &rt, const std::string &desc) {
//                    jsi::Value value =
//                            rt.global().getPropertyAsFunction(rt, "Error").call(rt, desc);
//                    return rt.valueRef(value);
//                }
//
//                static JSValueRef call(
//                        JSIProxyontextRef ctx,
//                        JSObjectRef function,
//                        JSObjectRef thisObject,
//                        size_t argumentCount,
//                        const JSValueRef arguments[],
//                        JSValueRef *exception) {
//                    HostFunctionMetadata *metadata =
//                            static_cast<HostFunctionMetadata *>(JSObjectGetPrivate(function));
//                    JSIProxyRuntime &rt = *(metadata->runtime);
//                    const unsigned maxStackArgCount = 8;
//                    jsi::Value stackArgs[maxStackArgCount];
//                    std::unique_ptr<jsi::Value[]> heapArgs;
//                    jsi::Value *args;
//                    if (argumentCount > maxStackArgCount) {
//                        heapArgs = std::make_unique<jsi::Value[]>(argumentCount);
//                        for (size_t i = 0; i < argumentCount; i++) {
//                            heapArgs[i] = rt.createValue(arguments[i]);
//                        }
//                        args = heapArgs.get();
//                    } else {
//                        for (size_t i = 0; i < argumentCount; i++) {
//                            stackArgs[i] = rt.createValue(arguments[i]);
//                        }
//                        args = stackArgs;
//                    }
//                    JSValueRef res;
//                    jsi::Value thisVal(rt.createObject(thisObject));
//                    try {
//                        res = rt.valueRef(
//                                metadata->hostFunction_(rt, thisVal, args, argumentCount));
//                    } catch (const jsi::JSError &error) {
//                        *exception = rt.valueRef(error.value());
//                        res = JSValueMakeUndefined(ctx);
//                    } catch (const std::exception &ex) {
//                        std::string exceptionString("Exception in HostFunction: ");
//                        exceptionString += ex.what();
//                        *exception = makeError(rt, exceptionString);
//                        res = JSValueMakeUndefined(ctx);
//                    } catch (...) {
//                        std::string exceptionString("Exception in HostFunction: <unknown>");
//                        *exception = makeError(rt, exceptionString);
//                        res = JSValueMakeUndefined(ctx);
//                    }
//                    return res;
//                }
//
//                static void finalize(JSObjectRef object) {
//                    HostFunctionMetadata *metadata =
//                            static_cast<HostFunctionMetadata *>(JSObjectGetPrivate(object));
//                    JSObjectSetPrivate(object, nullptr);
//                    delete metadata;
//                }
//
//                HostFunctionMetadata(
//                        JSIProxyRuntime *rt,
//                        jsi::HostFunctionType hf,
//                        unsigned ac,
//                        JSStringRef n)
//                        : HostFunctionProxy(hf),
//                          runtime(rt),
//                          argCount(ac),
//                          name(JSStringRetain(n)) {}
//
//                JSIProxyRuntime *runtime;
//                unsigned argCount;
//                JSStringRef name;
//            };

//            std::call_once(hostFunctionClassOnceFlag, []() {
//                JSIProxylassDefinition functionClass = kJSIProxylassDefinitionEmpty;
//                functionClass.version = 0;
//                functionClass.attributes = kJSIProxylassAttributeNoAutomaticPrototype;
//                functionClass.initialize = HostFunctionMetadata::initialize;
//                functionClass.finalize = HostFunctionMetadata::finalize;
//                functionClass.callAsFunction = HostFunctionMetadata::call;
//
//                hostFunctionClass = JSIProxylassCreate(&functionClass);
//            });
//
//            JSObjectRef funcRef = JSObjectMake(
//                    ctx_,
//                    hostFunctionClass,
//                    new HostFunctionMetadata(this, func, paramCount, stringRef(name)));
//            return createObject(funcRef).getFunction(*this);
}

//        namespace detail {
//
//            class ArgsConverter {
//            public:
//                ArgsConverter(JSIProxyRuntime &rt, const jsi::Value *args, size_t count) {
//                    JSValueRef *destination = inline_;
//                    if (count > maxStackArgs) {
//                        outOfLine_ = std::make_unique<JSValueRef[]>(count);
//                        destination = outOfLine_.get();
//                    }
//
//                    for (size_t i = 0; i < count; ++i) {
//                        destination[i] = rt.valueRef(args[i]);
//                    }
//                }
//
//                operator JSValueRef *() {
//                    return outOfLine_ ? outOfLine_.get() : inline_;
//                }
//
//            private:
//                constexpr static unsigned maxStackArgs = 8;
//                JSValueRef inline_[maxStackArgs];
//                std::unique_ptr<JSValueRef[]> outOfLine_;
//            };
//        } // namespace detail

bool JSIProxyRuntime::isHostFunction(const jsi::Function &obj) const {
//            auto cls = hostFunctionClass;
//            return cls != nullptr && JSValueIsObjectOfClass(ctx_, objectRef(obj), cls);
}

jsi::HostFunctionType &JSIProxyRuntime::getHostFunction(const jsi::Function &obj) {
    // We know that isHostFunction(obj) is true here, so its safe to proceed
//            auto proxy =
//                    static_cast<HostFunctionProxy *>(JSObjectGetPrivate(objectRef(obj)));
//            return proxy->getHostFunction();
}

jsi::Value JSIProxyRuntime::call(
        const jsi::Function &f,
        const jsi::Value &jsThis,
        const jsi::Value *args,
        size_t count) {
//            JSValueRef exc = nullptr;
//            auto res = JSObjectCallAsFunction(
//                    ctx_,
//                    objectRef(f),
//                    jsThis.isUndefined() ? nullptr : objectRef(jsThis.getObject(*this)),
//                    count,
//                    detail::ArgsConverter(*this, args, count),
//                    &exc);
//            checkException(exc);
//            return createValue(res);
}

jsi::Value JSIProxyRuntime::callAsConstructor(
        const jsi::Function &f,
        const jsi::Value *args,
        size_t count) {
//            JSValueRef exc = nullptr;
//            auto res = JSObjectCallAsConstructor(
//                    ctx_,
//                    objectRef(f),
//                    count,
//                    detail::ArgsConverter(*this, args, count),
//                    &exc);
//            checkException(exc);
//            return createValue(res);
}

bool JSIProxyRuntime::strictEquals(const jsi::Symbol &a, const jsi::Symbol &b)
const {
//            JSValueRef exc = nullptr;
//            bool ret = JSValueIsEqual(ctx_, symbolRef(a), symbolRef(b), &exc);
//            const_cast<JSIProxyRuntime *>(this)->checkException(exc);
//            return ret;
}

bool JSIProxyRuntime::strictEquals(const jsi::String &a, const jsi::String &b)
const {
//            return JSStringIsEqual(stringRef(a), stringRef(b));
}

bool JSIProxyRuntime::strictEquals(const jsi::Object &a, const jsi::Object &b)
const {
//            return objectRef(a) == objectRef(b);
}

bool JSIProxyRuntime::instanceOf(const jsi::Object &o, const jsi::Function &f) {
//            JSValueRef exc = nullptr;
//            bool res =
//                    JSValueIsInstanceOfConstructor(ctx_, objectRef(o), objectRef(f), &exc);
//            checkException(exc);
//            return res;
}

//        jsi::Runtime::PointerValue *JSIProxyRuntime::makeSymbolValue(
//                JSValueRef symbolRef) const {
//#ifndef NDEBUG
//            return new JSIProxySymbolValue(ctx_, ctxInvalid_, symbolRef, symbolCounter_);
//#else
//            return new JSIProxySymbolValue(ctx_, ctxInvalid_, symbolRef);
//#endif
//        }

//        namespace {
//            JSStringRef getEmptyString() {
//                static JSStringRef empty = JSStringCreateWithUTF8CString("");
//                return empty;
//            }
//        } // namespace

//        jsi::Runtime::PointerValue *JSIProxyRuntime::makeStringValue(
//                JSStringRef stringRef) const {
//            if (!stringRef) {
//                stringRef = getEmptyString();
//            }
//#ifndef NDEBUG
//            return new JSIProxyStringValue(stringRef, stringCounter_);
//#else
//            return new JSIProxyStringValue(stringRef);
//#endif
//        }

//        jsi::Symbol JSIProxyRuntime::createSymbol(JSValueRef sym) const {
//            return make<jsi::Symbol>(makeSymbolValue(sym));
//        }
//
//        jsi::String JSIProxyRuntime::createString(JSStringRef str) const {
//            return make<jsi::String>(makeStringValue(str));
//        }
//
//        jsi::PropNameID JSIProxyRuntime::createPropNameID(JSStringRef str) {
//            return make<jsi::PropNameID>(makeStringValue(str));
//        }

//        jsi::Runtime::PointerValue *JSIProxyRuntime::makeObjectValue(
//                JSObjectRef objectRef) const {
//            if (!objectRef) {
//                objectRef = JSObjectMake(ctx_, nullptr, nullptr);
//            }
//#ifndef NDEBUG
//            return new JSIProxyObjectValue(ctx_, ctxInvalid_, objectRef, objectCounter_);
//#else
//            return new JSIProxyObjectValue(ctx_, ctxInvalid_, objectRef);
//#endif
//        }
//
//        jsi::Object JSIProxyRuntime::createObject(JSObjectRef obj) const {
//            return make<jsi::Object>(makeObjectValue(obj));
//        }

//        jsi::Value JSIProxyRuntime::createValue(JSValueRef value) const {
//            JSType type = JSValueGetType(ctx_, value);
//
//            switch (type) {
//                case kJSTypeNumber:
//                    return jsi::Value(JSValueToNumber(ctx_, value, nullptr));
//                case kJSTypeBoolean:
//                    return jsi::Value(JSValueToBoolean(ctx_, value));
//                case kJSTypeNull:
//                    return jsi::Value(nullptr);
//                case kJSTypeUndefined:
//                    return jsi::Value();
//                case kJSTypeString: {
//                    JSStringRef str = JSValueToStringCopy(ctx_, value, nullptr);
//                    auto result = jsi::Value(createString(str));
//                    JSStringRelease(str);
//                    return result;
//                }
//                case kJSTypeObject: {
//                    JSObjectRef objRef = JSValueToObject(ctx_, value, nullptr);
//                    return jsi::Value(createObject(objRef));
//                }
//                    // TODO: Uncomment this when all supported JSIProxy versions have this symbol
//                    //    case kJSTypeSymbol:
//                default: {
//                    if (smellsLikeES6Symbol(ctx_, value)) {
//                        return jsi::Value(createSymbol(value));
//                    } else {
//                        // WHAT ARE YOU
//                        abort();
//                    }
//                }
//            }
//        }

    std::shared_ptr<aidl::com::example::remotejsi::IJSIValueInterface> JSIProxyRuntime::valueRef(const jsi::Value &value) {

        // return static_cast<const JSIProxySymbolValue *>(getPointerValue(value))->sym_;

            // TODO

            // I would rather switch on value.kind_
            /*if (value.isUndefined()) {
                return JSValueMakeUndefined(ctx_);
            } else if (value.isNull()) {
                return JSValueMakeNull(ctx_);
            } else if (value.isBool()) {
                return JSValueMakeBoolean(ctx_, value.getBool());
            } else if (value.isNumber()) {
                return JSValueMakeNumber(ctx_, value.getNumber());
            } else if (value.isSymbol()) {
                return symbolRef(value.getSymbol(*this));
            } else if (value.isString()) {
                return JSValueMakeString(ctx_, stringRef(value.getString(*this)));
            } else if (value.isObject()) {
                return objectRef(value.getObject(*this));
            } else*/ {
                // What are you?
                abort();
            }
        }

    std::shared_ptr<aidl::com::example::remotejsi::IJSISymbolInterface> JSIProxyRuntime::symbolRef(const jsi::Symbol &sym) {
            return static_cast<const JSIProxySymbolValue *>(getPointerValue(sym))->sym_;
        }

    std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> JSIProxyRuntime::stringRef(const jsi::String &str) {
            return static_cast<const JSIProxyStringValue *>(getPointerValue(str))->str_;
        }

    std::shared_ptr<aidl::com::example::remotejsi::IJSIStringInterface> JSIProxyRuntime::stringRef(const jsi::PropNameID &sym) {
            return static_cast<const JSIProxyStringValue *>(getPointerValue(sym))->str_;
        }

    std::shared_ptr<aidl::com::example::remotejsi::IJSIObjectInterface> JSIProxyRuntime::objectRef(const jsi::Object &obj) {
            return static_cast<const JSIProxyObjectValue *>(getPointerValue(obj))->obj_;
        }

//#ifdef RN_FABRIC_ENABLED
//        JSObjectRef JSIProxyRuntime::objectRef(const jsi::WeakObject &obj) {
//  // TODO: revisit this implementation
//  return static_cast<const JSIProxyObjectValue *>(getPointerValue(obj))->obj_;
//}
//#endif

//        void JSIProxyRuntime::checkException(JSValueRef exc) {
//            if (JSIProxy_UNLIKELY(exc)) {
//                throw jsi::JSError(*this, createValue(exc));
//            }
//        }
//
//        void JSIProxyRuntime::checkException(JSValueRef res, JSValueRef exc) {
//            if (JSIProxy_UNLIKELY(!res)) {
//                throw jsi::JSError(*this, createValue(exc));
//            }
//        }
//
//        void JSIProxyRuntime::checkException(JSValueRef exc, const char *msg) {
//            if (JSIProxy_UNLIKELY(exc)) {
//                throw jsi::JSError(std::string(msg), *this, createValue(exc));
//            }
//        }
//
//        void JSIProxyRuntime::checkException(
//                JSValueRef res,
//                JSValueRef exc,
//                const char *msg) {
//            if (JSIProxy_UNLIKELY(!res)) {
//                throw jsi::JSError(std::string(msg), *this, createValue(exc));
//            }
//        }

        std::unique_ptr<jsi::Runtime> makeJSIProxyRuntime(std::shared_ptr<aidl::com::example::remotejsi::IManagerInterface> managerService) {
            return std::make_unique<JSIProxyRuntime>(managerService);
        }
}