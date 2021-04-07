package com.jeremy.jndk.jni;

import com.jeremy.jndk.base.Animal;

public class JNIAccessField {
    static {
        System.loadLibrary("native-lib");
    }

    public static int num;

    public native void accessStaticField(Animal animal);

    public native void accessInstanceField(Animal animal);

    public static native void staticAccessInstanceField();
}
