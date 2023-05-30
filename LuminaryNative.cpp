#include <jni.h>
#include <stdio.h>
#include "Luminary.h"
#include "LuminaryNative.h"

JNIEXPORT jstring JNICALL Java_com_luminary_os_core_Native_getInfo(JNIEnv* env, jobject thisObject) {
    jstring result =  env->NewStringUTF("Luminary Native (Windows 1.0)");
    return result;
}
