#include <jni.h>

#include <GLEs2/gl2.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <android/bitmap.h>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <vector>

const GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


const char* vertexShader =
        "attribute vec3 inPosition;\n"
        "attribute vec2 inCoord;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "\n"
        "varying vec2 texCoord;\n"
        "void main()\n"
        "{\n"
        "    texCoord = inCoord;\n"
        "    gl_Position = projection * view * model * vec4(inPosition, 1.0);\n"
        "}";

const char* fragmentShader =
        "precision mediump float;\n"
        "varying vec2 texCoord;\n"
        "uniform sampler2D tex;\n"
        "void main()\n"
        "{\n"
        "    vec4 color = texture2D(tex, texCoord);\n"
        "    gl_FragColor = vec4(texCoord.x, texCoord.y, texCoord.x, 1.0);\n"
        "}";

class Engine {
public:
    void init(int width, int height) {
        this->width = width;
        this->height = height;
        createProgram();
        createVertexBuffer();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }

    void draw() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glm::mat4 model;
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(-1.0f, 1.0f, 0.0f));

        glm::mat4 view;
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

        float aspectRatio = (float)width / (float)height;
        glm::mat4 projection;
        projection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);


        GLint modelLoc = glGetUniformLocation(program, "model");
        GLint viewLoc = glGetUniformLocation(program, "view");
        GLint projectionLoc = glGetUniformLocation(program, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glDrawArrays(GL_TRIANGLES, 0, 36);

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
        auto x = sizeof(vertices);

        GLuint positionLoc = (GLuint)glGetAttribLocation(program, "inPosition");
        glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(positionLoc);
        GLuint textureLoc = (GLuint)glGetAttribLocation(program, "inCoord");
        glVertexAttribPointer(textureLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(textureLoc);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLuint program;
    GLuint vbo;
    int width;
    int height;
};

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

