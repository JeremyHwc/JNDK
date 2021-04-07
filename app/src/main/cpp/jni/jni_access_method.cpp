//
// Created by JeremyHwc on 2021/4/7.
//
#include <base.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIAccessMethod_accessStaticMethod(JNIEnv *env, jobject thiz,
                                                            jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jmethodID mid = env->GetStaticMethodID(cls, "callStaticMethod",
                                           "(Ljava/lang/String;)Ljava/lang/String;");
    jstring str = env->NewStringUTF("jstring");
    env->CallStaticObjectMethod(cls, mid, str);

    jmethodID sMid = env->GetStaticMethodID(cls, "callStaticMethod",
                                            "([Ljava/lang/String;I)Ljava/lang/String;");

    jclass strClass = env->FindClass("java/lang/String");
    int size = 2;
    jobjectArray strArray = env->NewObjectArray(size, strClass, nullptr);
    jstring strItem;
    for (int i = 0; i < size; i ++) {
        strItem = env->NewStringUTF("string in native");
        env->SetObjectArrayElement(strArray, i, strItem);
    }
    env->CallStaticObjectMethod(cls, sMid, strArray, size);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIAccessMethod_accessInstanceMethod(JNIEnv *env, jobject thiz,
                                                              jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jmethodID mid = env->GetMethodID(cls, "callInstanceMethod", "(I)V");
    env->CallVoidMethod(animal, mid, 2);
}
