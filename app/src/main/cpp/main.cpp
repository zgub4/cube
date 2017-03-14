#include <jni.h>

#include "Engine.h"

Engine engine;


extern "C" {
    JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_init(JNIEnv* env,
                                                                    jobject,
                                                                    jstring vertexSource,
                                                                    jstring fragmentSource);

    JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_resetAspectRatio(JNIEnv* env,
                                                                                jobject,
                                                                                int width,
                                                                                int height);

    JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_draw(JNIEnv* env, jobject);

    JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_startTouch(JNIEnv* env,
                                                                      jobject,
                                                                      float x,
                                                                      float y);

    JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_processTouch(JNIEnv* env,
                                                                            jobject,
                                                                            float x,
                                                                            float y);
}

JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_init(JNIEnv* env,
                                                                jobject,
                                                                jstring vertexSource,
                                                                jstring fragmentSource) {
    const char* vertex = env->GetStringUTFChars(vertexSource, 0);
    const char* fragment = env->GetStringUTFChars(fragmentSource, 0);
    engine.init(vertex, fragment);
}

JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_resetAspectRatio(JNIEnv* env,
                                                                            jobject,
                                                                            int width,
                                                                            int height) {
    engine.changeAspectRatio(width, height);
}

JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_draw(JNIEnv* env, jobject) {
    engine.draw();
}

JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_startTouch(JNIEnv* env,
                                                                      jobject,
                                                                      float x,
                                                                      float y) {
    engine.startTouch(x, y);
}

JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_processTouch(JNIEnv* env,
                                                                        jobject,
                                                                        float x,
                                                                        float y) {
    engine.processTouch(x, y);
}

