package com.jeremy.jndk.util;

import android.util.Log;

public class LogUtil {
    private static final String TAG = "JNDK";

    public static void i(String log) {
        Log.i(TAG, log);
    }
}
