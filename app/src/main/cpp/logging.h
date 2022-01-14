//
// Created by anandrag on 1/13/2022.
//

#ifndef REMOTEJSI_LOGGING_H
#define REMOTEJSI_LOGGING_H

#include <android/log.h>
#define LOGD(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##__VA_ARGS__)

#endif //REMOTEJSI_LOGGING_H
