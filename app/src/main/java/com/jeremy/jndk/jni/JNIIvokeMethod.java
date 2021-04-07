package com.jeremy.jndk.jni;

import com.jeremy.jndk.base.ICallbackMethod;
import com.jeremy.jndk.base.IThreadCallback;

public class JNIIvokeMethod {
    static {
        System.loadLibrary("dynamic-lib");
    }

    public native void nativeCallback(ICallbackMethod iCallbackMethod);

    public native void nativeThreadCallback(IThreadCallback iThreadCallback);
}
