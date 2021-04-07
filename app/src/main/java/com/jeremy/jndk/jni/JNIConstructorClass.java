package com.jeremy.jndk.jni;

import com.jeremy.jndk.base.Animal;

public class JNIConstructorClass {
    static {
        System.loadLibrary("native-lib");
    }

    public native Animal invokeAnimalConstructors();
    public native Animal allocObjectConstructor();
}
