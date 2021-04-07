package com.jeremy.jndk.jni;

import com.jeremy.jndk.base.Animal;

public class JNIAccessMethod {
    static {
        System.loadLibrary("native-lib");
    }

    public native void accessStaticMethod(Animal animal);

    public native void accessInstanceMethod(Animal animal);
}
