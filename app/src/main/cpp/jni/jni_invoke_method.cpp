//
// Created by JeremyHwc on 2021/4/4.
//

#include <base.h>
#include <pthread.h>
#include <jvm.h>

void *threadCallback(void *);

static jclass threadClazz;
static jmethodID threadMethod;
static jobject threadObject;

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIIvokeMethod_nativeCallback(JNIEnv *env, jobject thiz,
                                                       jobject callback) {
    LOGD("nativeCallback");
    jclass callbackClazz = env->GetObjectClass(callback);
    jmethodID callbackMethod = env->GetMethodID(callbackClazz, "callback", "()V");
    env->CallVoidMethod(callback, callbackMethod);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIIvokeMethod_nativeThreadCallback(JNIEnv *env, jobject thiz,
                                                             jobject callback) {
    threadObject = env->NewGlobalRef(callback);
    threadClazz = env->GetObjectClass(callback);
    threadMethod = env->GetMethodID(threadClazz, "callback", "()V");

    pthread_t handle;
    pthread_create(&handle, nullptr, threadCallback, nullptr);
}

void *threadCallback(void *) {
    // 注意JNIEnv是不可以跨线程的,所以需要在so库加载的时候，将JavaVm进行保存
    JavaVM *gVm = jvm::getJvm();
    JNIEnv *env = nullptr;
    if (gVm->AttachCurrentThread(&env, nullptr) == 0) {
        env->CallVoidMethod(threadObject, threadMethod);

        // DetachCurrentThread方法必须与AttachCurrentThread配套使用
        gVm->DetachCurrentThread();
    }
    return 0;
}