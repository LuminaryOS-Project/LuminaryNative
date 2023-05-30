#include <jni.h>
#include <stdio.h>
#include "Luminary.h"
#include "LuminaryNative.h"
#include "cmath"
JNIEXPORT jstring JNICALL Java_com_luminary_os_core_Native_getInfo(JNIEnv* env, jobject thisObject) {
    jstring result =  env->NewStringUTF("Luminary Native (Windows 1.0)");
    
    return result;
}

/*
Optimised for rendering Java ASCII surfaces.
*/
JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateX(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) + j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateY(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) - j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) - i * cos(B) * sin(C);
}

JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateZ(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}