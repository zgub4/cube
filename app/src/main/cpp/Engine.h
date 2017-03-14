#ifndef CUBE_ENGINE_H
#define CUBE_ENGINE_H

#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "vertices.h"

class Engine {
public:
    void init(int width, int height);
    void draw();

private:
    void createVertexBuffer();

    Shader shader;
    GLuint vbo;
    int width;
    int height;
};

#endif //CUBE_ENGINE_H
