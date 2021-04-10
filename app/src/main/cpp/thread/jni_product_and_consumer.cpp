//
// Created by JeremyHwc on 2021/4/9.
//
#include <base.h>
#include <queue>
#include <pthread.h>
#include <unistd.h>

using namespace std;
queue<int> data;
pthread_t consumer;
pthread_t producer;

pthread_mutex_t dataMutex;
pthread_cond_t dataCond;

void *productThread(void *) {
    while (data.size() < 10) {
        pthread_mutex_lock(&dataMutex);
        LOGD("生产物品");
        data.push(1);
        if (data.size() > 0) {
            LOGD("等待消费");
            pthread_cond_signal(&dataCond);
        }
        pthread_mutex_unlock(&dataMutex);
        sleep(3);
    }
    pthread_exit(0);
}

void *consumerThread(void *) {
    while (1) {
        pthread_mutex_lock(&dataMutex);
        if (data.size() > 0) {
            LOGI("消费物品");
            data.pop();
        } else {
            LOGI("等待生产");
            pthread_cond_wait(&dataCond, &dataMutex);
        }
        pthread_mutex_unlock(&dataMutex);
        sleep(3);
    }
    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIThread_startProductAndConsumerThread(JNIEnv *env, jobject thiz) {
    pthread_mutex_init(&dataMutex, nullptr);
    pthread_cond_init(&dataCond, nullptr);

    pthread_create(&consumer, nullptr, consumerThread, nullptr);
    pthread_create(&producer, nullptr, productThread, nullptr);
}