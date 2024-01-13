#include <jni.h>
#include <stdio.h>
#include "Luminary.h"
#include "LuminaryNative.h"
#include "cmath"
#include <string>


const char * get_version() {
    #ifdef _WIN64
    return "Luminary Native (Windows 64-bit / v1.0.0)";
    #elif _WIN32
    return "Luminary Native (Windows 32-bit / v1.0.0)";
    #elif __APPLE__ || __MACH__
    return "Luminary Native (Mac OSX / v1.0.0)";
    #elif __linux__
    return "Luminary Native (Linux / v1.0.0)";
    #elif __unix || __unix__
    return "Luminary Native (Unix / v1.0.0)";
    #else
    return "Luminary Native (Other / v1.0.0) *(THIS SHOULD NEVER HAPPEN IN PRODUCTION)";
    #endif
};

JNIEXPORT jstring JNICALL Java_com_luminary_os_core_Native_getInfo(JNIEnv* env, jobject thisObject) {
    jstring result =  env->NewStringUTF(get_version());
    return result;
}
/*
Optimised for rendering Java ASCII surfaces.
*/
/* #if defined(i386) || defined(__i386__) || defined(__i386)

#endif */
JNIEXPORT jstring JNICALL Java_com_luminary_os_core_Native_blacklistMethods(JNIEnv* env, jobject thisObject, jclass clazz, jobject blacklisted) {
    jclass reflClass = env->FindClass("jdk/internal/reflect/Reflection");
    if (reflClass == nullptr) {
        return env->NewStringUTF("CLASS_NOT_FOUND(NULLPTR)");
    }

    jmethodID rmtfmid = env->GetStaticMethodID(reflClass, "registerMethodsToFilter", "(Ljava/lang/Class;Ljava/util/Set;)V");
    if (rmtfmid == nullptr) {
        return env->NewStringUTF("METHOD_NOT_FOUND(NULLPTR)");
    }
    
    env->CallStaticVoidMethod(reflClass, rmtfmid, clazz, blacklisted);

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return env->NewStringUTF("EXCEPTION");
    }

    return env->NewStringUTF("SUCCESS");
}

JNIEXPORT jstring JNICALL Java_com_luminary_os_core_Native_blacklistFields(JNIEnv* env, jobject thisObject, jclass clazz, jobject blacklisted) {
    jclass reflClass = env->FindClass("jdk/internal/reflect/Reflection");
    if (reflClass == nullptr) {
        return env->NewStringUTF("CLASS_NOT_FOUND(NULLPTR)");
    }

    jmethodID rftfmid = env->GetStaticMethodID(reflClass, "registerFieldsToFilter", "(Ljava/lang/Class;Ljava/util/Set;)V");
    if (rftfmid == nullptr) {
        return env->NewStringUTF("METHOD_NOT_FOUND(NULLPTR)");
    }
    
    env->CallStaticVoidMethod(reflClass, rftfmid, clazz, blacklisted);

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return env->NewStringUTF("EXCEPTION");
    }

    return env->NewStringUTF("SUCCESS");
}

JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateX(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) + j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateY(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) - j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) - i * cos(B) * sin(C);
}

JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateZ(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}