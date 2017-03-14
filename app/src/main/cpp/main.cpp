#include <jni.h>

#include "Engine.h"

Engine engine;


extern "C" {
    JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_init(JNIEnv* env, jobject, int width, int height);
    JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_draw(JNIEnv* env, jobject);
}

JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_init(JNIEnv* env, jobject, int width, int height) {
    engine.init(width, height);
}

JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_draw(JNIEnv* env, jobject) {
    engine.draw();
}

