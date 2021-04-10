//
// Created by JeremyHwc on 2021/4/4.
//
#include <base.h>
// pthread头文件几乎涵盖了线程的所有操作
#include <pthread.h>
#include <unistd.h>

void *printThreadHello(void *) {
    LOGD("hello thread");
    // 显式让线程退出
    pthread_exit(0);
//    return nullptr;
}

struct ThreadRunArgs {
    int id;
    int result;
};

void *printThreadArgs(void *arg) {
    ThreadRunArgs *args = static_cast<ThreadRunArgs *>(arg);
    LOGD("thread id is %d", args->id);
    LOGD("thread result is %d", args->result);
    return nullptr;
}

void *printThreadJoin(void *arg) {
    ThreadRunArgs *args = static_cast<ThreadRunArgs *>(arg);
    struct timeval begin;
    gettimeofday(&begin, nullptr);

    sleep(3);

    struct timeval end;
    gettimeofday(&end, nullptr);

    LOGD("Time used is %d", end.tv_sec - begin.tv_sec);
    return reinterpret_cast<void *>(args->result);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIThread_createNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t handles;
    int result = pthread_create(&handles, nullptr, printThreadHello, nullptr);
    if (result == 0) {
        LOGD("Create thread success");
    } else {
        LOGD("Create thread failed");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIThread_createNativeThreadWithArgs(JNIEnv *env, jobject thiz) {
    pthread_t handles;
    ThreadRunArgs *args = new ThreadRunArgs;
    args->id = 2;
    args->result = 100;
    int result = pthread_create(&handles, nullptr, printThreadArgs, args);
    if (result == 0) {
        LOGD("Create thread success");
    } else {
        LOGD("Create thread failed");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIThread_joinNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t handles;
    ThreadRunArgs *args = new ThreadRunArgs;
    args->id = 2;
    args->result = 100;
    int result = pthread_create(&handles, nullptr, printThreadJoin, args);
    if (result == 0) {
        LOGD("Create thread success");
    } else {
        LOGD("Create thread failed");
    }
    void *ret = nullptr;
    // Java_com_jeremy_jndk_jni_JNIThread_joinNativeThread方法是在主线程被调用，这里调用pthread_join后会挂起主线程，等待子线程执行结束
    pthread_join(handles, &ret);
    LOGD("result is %d",ret);
}