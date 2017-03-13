#include <jni.h>

#include <GLEs2/gl2.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <android/bitmap.h>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <vector>

const GLfloat vertices[] = {
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
};

const GLint indices[] = {
        0, 1, 2, 1, 2, 3
};

const char* vertexShader =
        "attribute vec4 inPosition;\n"
        "attribute vec2 inCoord;\n"
        "varying vec2 texCoord;\n"
        "void main()\n"
        "{\n"
        "    texCoord = inCoord;\n"
        "    gl_Position = inPosition;\n"
        "}";

const char* fragmentShader =
        "precision mediump float;\n"
        "varying vec2 texCoord;\n"
        "uniform sampler2D tex;\n"
        "void main()\n"
        "{\n"
        "    vec4 color = texture2D(tex, texCoord);\n"
        "    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "}";

class Engine {
public:
    void init(int width, int height, AAssetManager* manager) {
        assetManager = manager;
        createProgram();
        createVertexBuffer();
        createTexture();
    }

    void draw() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindTexture(GL_TEXTURE_2D, texture);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
private:
    void createProgram() {
        GLuint vertex = createShader(GL_VERTEX_SHADER, vertexShader);
        GLuint fragment = createShader(GL_FRAGMENT_SHADER, fragmentShader);
        program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if(status == GL_FALSE) {
            GLint length = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            std::vector <GLchar> errorLog(length);
            glGetProgramInfoLog(program, length, &length, &errorLog[0]);
            // Log error
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    GLuint createShader(GLenum type, const char* source) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if(status == GL_FALSE) {
            GLint length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            std::vector <GLchar> errorLog(length);
            glGetShaderInfoLog(shader, length, &length, &errorLog[0]);
            // Log error
            return 0;
        }
        return shader;
    }

    void createVertexBuffer() {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

        GLuint positionLoc = (GLuint)glGetAttribLocation(program, "inPosition");
        glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(positionLoc);
        GLuint textureLoc = (GLuint)glGetAttribLocation(program, "inCoord");
        glVertexAttribPointer(textureLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(textureLoc);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void createTexture() {
        AAsset* asset = AAssetManager_open(assetManager, "bricks.jpg", AASSET_MODE_UNKNOWN);
        if(asset == nullptr) {

        }

        GLuint bufferSize = 256*258*4;
        GLubyte buffer[bufferSize];
        GLubyte* data = (GLubyte*)AAsset_read(asset, buffer, bufferSize);
        if(data == nullptr) {

        }

        

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    GLuint program;
    GLuint vbo;
    GLuint texture;
    AAssetManager* assetManager;
};

Engine engine;


extern "C" {
    JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_init(JNIEnv* env, jobject, int width, int height, jobject assetManager);
    JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_draw(JNIEnv* env, jobject);
}

JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_init(JNIEnv* env, jobject, int width, int height, jobject assetManager) {
    engine.init(width, height, AAssetManager_fromJava(env, assetManager));
}

JNIEXPORT void JNICALL Java_pw_robertlewicki_cube_Renderer_draw(JNIEnv* env, jobject) {
    engine.draw();
}

