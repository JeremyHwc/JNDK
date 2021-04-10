package com.jeremy.jndk;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.jeremy.jndk.base.Animal;
import com.jeremy.jndk.jni.JNIAccessField;
import com.jeremy.jndk.jni.JNIAccessMethod;
import com.jeremy.jndk.jni.JNIBasicType;
import com.jeremy.jndk.jni.JNIBitmap;
import com.jeremy.jndk.jni.JNIConstructorClass;
import com.jeremy.jndk.jni.JNIException;
import com.jeremy.jndk.jni.JNIReference;
import com.jeremy.jndk.jni.JNIReferenceType;
import com.jeremy.jndk.jni.JNIString;
import com.jeremy.jndk.load.JNIDynamicLoad;
import com.jeremy.jndk.util.LogUtil;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /*JNIDynamicLoad jniDynamicLoad = new JNIDynamicLoad();
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        tv.setOnClickListener(v -> tv.setText(jniDynamicLoad.getNativeString()));*/
//        testJNIBasicType();
//        testJniString();
//        testJNIReferenceType();
//        testJniAccessField();
//        testJniAccessMethod();
//        testJNIConstructorClass();
//        testJniReference();
//        testJniException();
        ImageView imageView = findViewById(R.id.bitmap);
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.ic_launcher);
        JNIBitmap jniBitmap = new JNIBitmap();
        imageView.setOnClickListener(v -> {
            Bitmap result = jniBitmap.callNativeMirrorBitmap(bitmap);
            imageView.setImageBitmap(result);
        });

    }

    private void testJniException() {
        JNIException jniException = new JNIException();
        findViewById(R.id.sample_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    jniException.nativeThrowException();
                } catch (IllegalArgumentException e) {
                    LogUtil.i(e.getMessage());
                }
                jniException.nativeInvokeJavaException();
            }
        });
    }

    private void testJniReference() {
        JNIReference jniReference = new JNIReference();
        findViewById(R.id.sample_button).setOnClickListener(v -> {
            jniReference.errorCacheLocalReference();
            jniReference.useWeakGlobalReference();
            jniReference.cacheWithGlobalReference();
        });
    }

    private void testJNIConstructorClass() {
        JNIConstructorClass jniConstructorClass = new JNIConstructorClass();
        findViewById(R.id.sample_button).setOnClickListener(v -> {
            LogUtil.i("name is " + jniConstructorClass.allocObjectConstructor().getName());
            LogUtil.i("name is " + jniConstructorClass.invokeAnimalConstructors().getName());
        });
    }

    private void testJniAccessMethod() {
        JNIAccessMethod jniAccessMethod = new JNIAccessMethod();
        Animal animal = new Animal("animal");
        findViewById(R.id.sample_button).setOnClickListener(v -> {
            jniAccessMethod.accessInstanceMethod(animal);
            jniAccessMethod.accessStaticMethod(animal);
        });
    }

    private void testJniAccessField() {
        JNIAccessField jniAccessField = new JNIAccessField();
        Animal animal = new Animal("animal");
        findViewById(R.id.sample_button).setOnClickListener(v -> {
            jniAccessField.accessStaticField(animal);
            jniAccessField.accessInstanceField(animal);
            JNIAccessField.staticAccessInstanceField();
            LogUtil.i("name is " + animal.getName());
            LogUtil.i("num is " + Animal.getNum());
            LogUtil.i("num is " + JNIAccessField.num);
        });
    }

    private void testJNIReferenceType() {
        String[] contents = {"apple", "pear", "banana"};
        JNIReferenceType jniReferenceType = new JNIReferenceType();
        findViewById(R.id.sample_button).setOnClickListener(v -> LogUtil.i("Array Item is " + jniReferenceType.callNativeStringArray(contents)));
    }

    private void testJniString() {
        JNIString jniString = new JNIString();
        findViewById(R.id.sample_button).setOnClickListener(v -> {
            LogUtil.i(jniString.callNativeString("java string"));
            jniString.stringMethod("java string");
        });
    }

    private void testJNIBasicType() {
        JNIBasicType jniBasicType = new JNIBasicType();
        findViewById(R.id.sample_button).setOnClickListener(v -> {
            LogUtil.i("java show " + jniBasicType.callNativeChar('A'));
            LogUtil.i("java show " + jniBasicType.callNativeByte((byte) 2));
            LogUtil.i("java show " + jniBasicType.callNativeShort((short) 2));
            LogUtil.i("java show " + jniBasicType.callNativeInt(2));
            LogUtil.i("java show " + jniBasicType.callNativeLong(2));
            LogUtil.i("java show " + jniBasicType.callNativeFloat(2));
            LogUtil.i("java show " + jniBasicType.callNativeDouble(2));
            LogUtil.i("java show " + jniBasicType.callNativeBoolean(false));
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String getString();
}