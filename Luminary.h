#include <stdio.h>
#include <jni.h>
#ifndef LUMINARY_H
#define LUMINARY_H
#pragma once

class NativeRef {
    jobject obj;
    jclass clazz;
    public:
        NativeRef(const jobject obj, const jclass clazz) {
            this->obj = obj;
            this->clazz = clazz;
        }
        ~NativeRef() = default;
        [[nodiscard]] jobject getObject() const { return this->obj; }
        [[nodiscard]] jclass getClass() const { return this->clazz; }
};

enum State {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED
};
#endif