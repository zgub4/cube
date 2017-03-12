#include <jni.h>

#include <GLEs2/gl2.h>

const GLfloat vertices[] = {
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

const char* vertexShader = "attribute vec4 inPosition; void main() { gl_Position = inPosition; }";
const char* fragmentShader = "precision mediump float; void main() { gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); }";

class Engine {
public:
    void init(int width, int height) {
        createProgram();
        createVertexBuffer();
        // Consider using glViewport after rotation
    }

    void draw() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glDrawArrays(GL_TRIANGLES, 0, 3);

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

        }
        return shader;
    }

    void createVertexBuffer() {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
        GLuint attributeLocation = (GLuint)glGetAttribLocation(program, "inPosition");
        glVertexAttribPointer(attributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(attributeLocation);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    GLuint program;
    GLuint vbo;
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

