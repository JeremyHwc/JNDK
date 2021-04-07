//
// Created by JeremyHwc on 2021/4/4.
//

#ifndef JNDK_BASE_H
#define JNDK_BASE_H

#include <jni.h>
#include <android/log.h>

#define LOG_TAG "JNDK"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif //JNDK_BASE_H

