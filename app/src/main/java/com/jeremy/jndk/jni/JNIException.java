package com.jeremy.jndk.jni;

public class JNIException {
    static {
        System.loadLibrary("native-lib");
    }

    public native void nativeInvokeJavaException();

    // Native中抛出异常，交由上层进行处理
    public native void nativeThrowException() throws IllegalArgumentException;

    private int operation() {
        return 2/0;
    }
}
