package com.jeremy.jndk.jni;

import android.graphics.Bitmap;

public class JNIThread {
    static {
        System.loadLibrary("dynamic-lib");
    }

    public native void createNativeThread();

    public native void createNativeThreadWithArgs();

    public native void joinNativeThread();

    public native void waitNativeThread();

    public native void notifyNativeThread();

    public native Bitmap startProductAndConsumerThread();
}
