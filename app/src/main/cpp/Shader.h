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

    GLuint getId() {return program;}

private:
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

    GLuint program;
};

#endif //CUBE_SHADER_H
