package com.jeremy.jndk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.jeremy.jndk.base.ICallbackMethod;
import com.jeremy.jndk.base.IThreadCallback;
import com.jeremy.jndk.jni.JNIIvokeMethod;
import com.jeremy.jndk.util.LogUtil;

public class JniActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni);
        JNIIvokeMethod jniIvokeMethod = new JNIIvokeMethod();
        findViewById(R.id.button).setOnClickListener(v -> {
            jniIvokeMethod.nativeCallback(() ->
                    LogUtil.i("thread name is " + Thread.currentThread().getName())
            );
            jniIvokeMethod.nativeThreadCallback(() ->
                    LogUtil.i("thread name is " + Thread.currentThread().getName())
            );
        });
    }
}