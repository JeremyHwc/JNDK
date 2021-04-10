//
// Created by JeremyHwc on 2021/4/8.
//

#include <base.h>
#include <pthread.h>
#include <stdio.h>
#include <jvm.h>
#include <unistd.h>
#include <queue>

// 互斥锁。同一时刻只允许一个线程对临界资源进行操作。互斥锁使用不当很可能造成线程之间的死锁。
pthread_mutex_t mutex;
// 条件变量。用来实现线程之间的唤醒和释放，可以控制线程之间进行等待
pthread_cond_t cond;

// 线程句柄
pthread_t waitHandle;
pthread_t notifyHandle;

int flag = 0;

// 疑问：为什么在pthread_cond_wait之前需要调用pthread_mutex_lock(&mutex)？
// 可以避免notify thread先执行，导致的唤醒丢失的问题。

void *waitThread(void *) {
    LOGD("wait thread lock");
    pthread_mutex_lock(&mutex);
    while (flag == 0) {
        LOGD("waiting");
        // 调用该方法时，线程就会等待挂起。通过cond进行唤醒
        pthread_cond_wait(&cond, &mutex);
    }
    LOGD("wait thread unlock");
    pthread_mutex_unlock(&mutex);
    // 如果不添加退出函数，运行的时候程序就会崩溃
    pthread_exit(0);
}

void *notifyThread(void *) {
    LOGD("notify thread lock");
    pthread_mutex_lock(&mutex);
    flag = 1;
    pthread_mutex_unlock(&mutex);

    pthread_cond_signal(&cond);
    LOGD("notify thread unlock");
    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIThread_waitNativeThread(JNIEnv *env, jobject thiz) {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_create(&waitHandle, nullptr, waitThread, nullptr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIThread_notifyNativeThread(JNIEnv *env, jobject thiz) {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_create(&notifyHandle, nullptr, notifyThread, nullptr);
}
