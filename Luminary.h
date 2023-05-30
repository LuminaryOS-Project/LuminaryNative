#include <stdio.h>
#include <jni.h>
#ifndef LUMINARY_H
#define LUMINARY_H
#pragma once
struct Point {
    int x;
    int y;
};

class NativeRef {
    private:
        jobject obj;
        jclass clazz;
    public:
        NativeRef(jobject obj, jclass clazz) {
            this->obj = obj;
            this->clazz = clazz;
        }
        ~NativeRef() {}
        jobject getObject() { return this->obj; }
        jclass getClass() { return this->clazz; }
};

enum State {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED
};
#endif