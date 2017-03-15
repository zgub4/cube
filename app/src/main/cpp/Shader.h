#ifndef CUBE_SHADER_H
#define CUBE_SHADER_H

#include <GLES2/gl2.h>
#include <vector>

class Shader {
public:
    void createProgram(const char* vertexSource, const char* fragmentSource) {
        GLuint vertex = createShader(GL_VERTEX_SHADER, vertexSource);
        GLuint fragment = createShader(GL_FRAGMENT_SHADER, fragmentSource);
        program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        assert(status != GL_FALSE);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    GLuint getId() {return program;}

private:
    GLuint createShader(GLenum type, const char* source) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        assert(status != GL_FALSE);
        return shader;
    }

    GLuint program;
};

#endif //CUBE_SHADER_H
