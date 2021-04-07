//
// Created by JeremyHwc on 2021/4/7.
//

#include <base.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIAccessField_accessStaticField(JNIEnv *env, jobject thiz,
                                                          jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jfieldID fid = env->GetStaticFieldID(cls, "num", "I");
    jint num = env->GetStaticIntField(cls, fid);
    env->SetStaticIntField(cls, fid, ++num);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIAccessField_accessInstanceField(JNIEnv *env, jobject thiz,
                                                            jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jfieldID fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
    jstring str = env->NewStringUTF("this is new name");
    env->SetObjectField(animal, fid, str);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIAccessField_staticAccessInstanceField(JNIEnv *env, jclass cls) {
    jfieldID fid = env->GetStaticFieldID(cls, "num", "I");
    jint num = env->GetStaticIntField(cls, fid);
    env->SetStaticIntField(cls, fid, ++num);
}