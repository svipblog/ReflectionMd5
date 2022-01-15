package dev.svip.reflectionmd5;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.text.TextUtils;
import android.widget.TextView;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import dev.svip.reflectionmd5.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'reflectionmd5' library on application startup.
    static {
        System.loadLibrary("reflectionmd5");
    }

    private ActivityMainBinding binding;

    @SuppressLint("MissingSuperCall")
    @Override
    protected native void onCreate(Bundle savedInstanceState);

//        @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//
//        binding = ActivityMainBinding.inflate(getLayoutInflater());
//        setContentView(binding.getRoot());
//
//        // Example of a call to a native method
//        TextView tv = binding.sampleText;
//        tv.append(System.lineSeparator());
//        tv.append("java md5 => " + Javamd5("blog.svip.dev") + System.lineSeparator());
//        tv.append("refe md5 => " + Refmd5("blog.svip.dev") + System.lineSeparator());
//        tv.append("refe java md5 => " + Refmd5Second("blog.svip.dev") + System.lineSeparator());
//    }

    /**
     * A native method that is implemented by the 'reflectionmd5' native library,
     * which is packaged with this application.
     */
    public native static String Refmd5(String string);

    public native String Refmd5Second(String string);

    public String Javamd5(String string) {
        if (TextUtils.isEmpty(string)) {
            return "";
        }
        MessageDigest md5 = null;
        try {
            md5 = MessageDigest.getInstance("MD5");
            byte[] bytes = md5.digest(string.getBytes());
            StringBuilder result = new StringBuilder();
            for (byte b : bytes) {
                String temp = Integer.toHexString(b & 0xff);
                if (temp.length() == 1) {
                    temp = "0" + temp;
                }
                result.append(temp);
            }
            return result.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return "";
    }
}