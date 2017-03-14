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
    void init(const char* vertexSource, const char* fragmentSource);
    void changeAspectRatio(int width, int height);
    void draw();
    void startTouch(float x, float y);
    void processTouch(float x, float y);

private:
    void createVertexBuffer();

    Shader shader;
    GLuint vbo;
    int width;
    int height;
    glm::vec2 startTouchPosition{0.0f, 0.0f};
    glm::vec3 currentRotation{1.0f, 1.0f, 0.0f};
    glm::mat4 projection;
};

#endif //CUBE_ENGINE_H
