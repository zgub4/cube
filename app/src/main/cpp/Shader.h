#ifndef CUBE_SHADER_H
#define CUBE_SHADER_H

#include <GLES2/gl2.h>
#include <vector>

class Shader {
public:
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

    void use() {
        glUseProgram(program);
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
};

#endif //CUBE_SHADER_H
