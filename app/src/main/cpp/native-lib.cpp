#include <jni.h>
#include <string>

#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

extern "C"
JNIEXPORT jstring JNICALL
Java_dev_svip_reflectionmd5_MainActivity_Refmd5(JNIEnv *env, jclass clazz, jstring string) {
//    MessageDigest md5 = MessageDigest.getInstance("MD5");
    jclass MessageDigest = env -> FindClass("java/security/MessageDigest");
    jmethodID getInstance = env -> GetStaticMethodID(MessageDigest, "getInstance",
                                                     "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jstring MD5 = env -> NewStringUTF("MD5");
    jobject md5 = env -> CallStaticObjectMethod(MessageDigest, getInstance, MD5);

//    byte[] bytes = md5.digest(string.getBytes());
    jmethodID digest = env -> GetMethodID(MessageDigest, "digest", "([B)[B");
    jclass stringClass = env -> FindClass("java/lang/String");
    jmethodID getBytes = env -> GetMethodID(stringClass, "getBytes", "()[B");
    auto jba = (env -> CallObjectMethod(string, getBytes));
    jbyteArray md5result = static_cast<jbyteArray>(env -> CallObjectMethod(md5, digest, jba));

    char *cmd5 = reinterpret_cast<char *>(env -> GetByteArrayElements(md5result, 0));

    char dest[32] = {0};
    for (int i = 0; i < 16; ++i) {
        sprintf(dest + i * 2, "%02x", cmd5[i]);
    }
    return env -> NewStringUTF(dest);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_dev_svip_reflectionmd5_MainActivity_Refmd5Second(JNIEnv *env, jobject obj, jstring string) {
    jclass MainActivity = env -> FindClass("dev/svip/reflectionmd5/MainActivity");
    jmethodID Javamd5 = env -> GetMethodID(MainActivity, "Javamd5",
                                           "(Ljava/lang/String;)Ljava/lang/String;");
    jstring result = static_cast<jstring>(env -> CallObjectMethod(obj, Javamd5, string));
    return result;
}

void ffff(JNIEnv *env, jobject thiz,
          jobject saved_instance_state) {
    // super.onCreate(savedInstanceState);
    jclass FragmentActivity = env -> FindClass("androidx/fragment/app/FragmentActivity");
    jmethodID onCreate = env -> GetMethodID(FragmentActivity, "onCreate", "(Landroid/os/Bundle;)V");
    env -> CallNonvirtualVoidMethod(thiz, FragmentActivity, onCreate, saved_instance_state);


    // binding = ActivityMainBinding.inflate(getLayoutInflater());
    jclass LayoutInflater = env -> FindClass("dev/svip/reflectionmd5/MainActivity");
    jmethodID getLayoutInflater = env -> GetMethodID(LayoutInflater, "getLayoutInflater",
                                                     "()Landroid/view/LayoutInflater;");
    jclass ActivityMainBinding = env -> FindClass(
            "dev/svip/reflectionmd5/databinding/ActivityMainBinding");
    jmethodID inflate = env -> GetStaticMethodID(ActivityMainBinding, "inflate",
                                                 "(Landroid/view/LayoutInflater;)Ldev/svip/reflectionmd5/databinding/ActivityMainBinding;");

    jobject ret_getLayoutInflater = env -> CallNonvirtualObjectMethod(thiz, LayoutInflater,
                                                                      getLayoutInflater);
    jobject binding = env -> CallStaticObjectMethod(ActivityMainBinding, inflate,
                                                    ret_getLayoutInflater);

    // setContentView(binding.getRoot());
    jclass MainActivity = env -> FindClass("dev/svip/reflectionmd5/MainActivity");
    jmethodID setContentView = env -> GetMethodID(MainActivity, "setContentView",
                                                  "(Landroid/view/View;)V");

    jmethodID getRoot = env -> GetMethodID(ActivityMainBinding, "getRoot",
                                           "()Landroidx/constraintlayout/widget/ConstraintLayout;");

    jobject ret_getRoot = env -> CallObjectMethod(binding, getRoot);

    env -> CallVoidMethod(thiz, setContentView, ret_getRoot);

    // TextView tv = binding.sampleText;
    jfieldID sampleText = env -> GetFieldID(ActivityMainBinding, "sampleText",
                                            "Landroid/widget/TextView;");
    jobject tv = env -> GetObjectField(binding, sampleText);

    // tv.append("\nblog.svip.dev");
    jclass TextView = env -> FindClass("android/widget/TextView");
    jmethodID append = env -> GetMethodID(TextView, "append", "(Ljava/lang/CharSequence;)V");
    env -> CallVoidMethod(tv, append, env -> NewStringUTF("\nblog.svip.dev"));
}


static JNINativeMethod method_table[] = {
        {"onCreate", "(Landroid/os/Bundle;)V", (void *) ffff},
};

static int
registerMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods, int numMethods) {
    jclass clazz = env -> FindClass(className);
    if (clazz == nullptr) {
        return JNI_FALSE;
    }
    if (env -> RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    if (vm -> GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    //注册native方法
    if (!registerMethods(env, "dev/svip/reflectionmd5/MainActivity", method_table,
                         NELEM(method_table))) {
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}