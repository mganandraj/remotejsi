//
// Created by anandrag on 1/14/2022.
//

#include "JSIBufferService.h"

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIBufferInterface.h>

#define LOG_TAG "JSIBufferService"
#include "logging.h"

#include <jsi/jsi.h>

namespace aidl::com::example::remotejsi {

JSIBufferService::JSIBufferService(const std::shared_ptr<const facebook::jsi::Buffer> buffer) : buffer_(std::move(buffer)) {}

::ndk::ScopedAStatus JSIBufferService::data(std::vector<int8_t>* _aidl_return) {
    // std::vector<int8_t> vec = std::vector<int8_t>(reinterpret_cast<int8_t*>(const_cast<uint8_t*>(buffer_->data())), reinterpret_cast<int8_t*>(const_cast<uint8_t*>(buffer_->data() + buffer_->size())));;
    // std::vector<int8_t> vec = std::vector<int8_t>();
    //for (int8_t i: vec) {
        // _aidl_return->push_back(0);
    //}
    * _aidl_return = std::vector<int8_t>(reinterpret_cast<int8_t*>(const_cast<uint8_t*>(buffer_->data())), reinterpret_cast<int8_t*>(const_cast<uint8_t*>(buffer_->data() + buffer_->size())));;
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIBufferService::size(int64_t* _aidl_return) {
    *_aidl_return = buffer_->size();
    return ::ndk::ScopedAStatus::ok();
}

}