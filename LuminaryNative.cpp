#include <jni.h>
#include <stdio.h>
#include "Luminary.h"
#include "LuminaryNative.h"
#include "cmath"
#include <immintrin.h>
#include <string>

__m128 load(float value) {
    return _mm_set1_ps(value);
}

const char * get_version() {
    #ifdef _WIN64
    return "Luminary Native (Windows 64-bit)";
    #elif _WIN32
    return "Luminary Native (Windows 32-bit)";
    #elif __APPLE__ || __MACH__
    return "Luminary Native (Mac OSX)";
    #elif __linux__
    return "Luminary Native (Linux)";
    #elif __unix || __unix__
    return "Luminary Native (Unix)";
    #else
    return "Luminary Native (Other) *(THIS SHOULD NEVER HAPPEN IN PRODUCTION)";
    #endif
};

JNIEXPORT jstring JNICALL Java_com_luminary_os_core_Native_getInfo(JNIEnv* env, jobject thisObject) {
    jstring result =  env->NewStringUTF("Luminary Native (Windows 1.0)");
    return result;
}
/*
Optimised for rendering Java ASCII surfaces.
*/
/* #if defined(i386) || defined(__i386__) || defined(__i386)

#endif */
JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateX(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    __m128 sinA = load(sin(A));
    __m128 sinB = load(sin(B));
    __m128 cosC = load(cos(C));
    __m128 cosA = load(cos(A));
    __m128 sinC = load(sin(C));
    __m128 cosB = load(cos(B));

    __m128 jVec = _mm_set1_ps(static_cast<float>(j));
    __m128 kVec = _mm_set1_ps(static_cast<float>(k));
    __m128 iVec = _mm_set1_ps(static_cast<float>(i));

    __m128 result = _mm_add_ps(_mm_mul_ps(_mm_mul_ps(_mm_mul_ps(jVec, sinA), sinB), cosC),
                               _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_mul_ps(kVec, cosA), sinB), _mm_mul_ps(jVec, cosA)), _mm_add_ps(_mm_mul_ps(kVec, sinA), _mm_mul_ps(iVec, cosB))));

    float x;
    _mm_store_ss(&x, result);

    return x;
}
JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateY(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    __m128 cosA = _mm_set1_ps(std::cos(A));
    __m128 cosB = _mm_set1_ps(std::cos(B));
    __m128 cosC = _mm_set1_ps(std::cos(C));
    __m128 sinA = _mm_set1_ps(std::sin(A));
    __m128 sinB = _mm_set1_ps(std::sin(B));
    __m128 sinC = _mm_set1_ps(std::sin(C));

    __m128 jValues = _mm_set1_ps(static_cast<float>(j));
    __m128 kValues = _mm_set1_ps(static_cast<float>(k));
    __m128 iValues = _mm_set1_ps(static_cast<float>(i));

    __m128 term1 = _mm_mul_ps(jValues, _mm_mul_ps(cosA, cosC));
    __m128 term2 = _mm_mul_ps(kValues, _mm_mul_ps(sinA, cosC));
    __m128 term3 = _mm_mul_ps(jValues, _mm_mul_ps(sinA, _mm_mul_ps(sinB, sinC)));
    __m128 term4 = _mm_mul_ps(kValues, _mm_mul_ps(cosA, _mm_mul_ps(sinB, sinC)));
    __m128 term5 = _mm_mul_ps(iValues, _mm_mul_ps(cosB, sinC));

    __m128 result = _mm_sub_ps(_mm_add_ps(_mm_sub_ps(_mm_add_ps(term1, term2), term3), term4), term5);

    alignas(16) float resultArray[4];
    _mm_store_ps(resultArray, result);

    return resultArray[0];
};

JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateZ(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    __m128 cosA = _mm_set1_ps(std::cos(A));
    __m128 cosB = _mm_set1_ps(std::cos(B));
    __m128 sinA = _mm_set1_ps(std::sin(A));
    __m128 sinB = _mm_set1_ps(std::sin(B));

    __m128 jValues = _mm_set1_ps(static_cast<float>(j));
    __m128 kValues = _mm_set1_ps(static_cast<float>(k));
    __m128 iValues = _mm_set1_ps(static_cast<float>(i));

    __m128 term1 = _mm_mul_ps(kValues, _mm_mul_ps(cosA, cosB));
    __m128 term2 = _mm_mul_ps(jValues, _mm_mul_ps(sinA, cosB));
    __m128 term3 = _mm_mul_ps(iValues, sinB);

    __m128 result = _mm_add_ps(_mm_sub_ps(term1, term2), term3);

    alignas(16) float resultArray[4];
    _mm_store_ps(resultArray, result);

    return resultArray[0];
};


/*JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateX(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) + j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateY(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) - j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) - i * cos(B) * sin(C);
}

JNIEXPORT jfloat JNICALL Java_com_luminary_os_core_Native_calculateZ(JNIEnv* env, jobject thisObject, jint i, jint j, jint k, jfloat A, jfloat B, jfloat C) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}*/