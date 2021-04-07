package com.jeremy.jndk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.jeremy.jndk.jni.JNIThread;

public class ThreadStartActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_thread_start);

        JNIThread jniThread = new JNIThread();
        findViewById(R.id.button1).setOnClickListener((v) -> jniThread.createNativeThread());
        findViewById(R.id.button2).setOnClickListener((v) -> jniThread.createNativeThreadWithArgs());
        findViewById(R.id.button3).setOnClickListener((v) -> jniThread.joinNativeThread());
    }
}