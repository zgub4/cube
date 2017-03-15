#include "Engine.h"

void Engine::init(const char* vertexSource, const char* fragmentSource) {
    shader.createProgram(vertexSource, fragmentSource);
    createVertexBuffer();
    glEnable(GL_DEPTH_TEST);
}

void Engine::changeAspectRatio(int width, int height) {
    this->width = width;
    this->height = height;
    projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

void Engine::draw() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader.getId());
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 model;
    model = glm::rotate(model, glm::radians(90.0f), currentRotation);

    glm::mat4 view;
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

    GLint modelLoc = glGetUniformLocation(shader.getId(), "model");
    GLint viewLoc = glGetUniformLocation(shader.getId(), "view");
    GLint projectionLoc = glGetUniformLocation(shader.getId(), "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::createVertexBuffer() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    GLuint positionLoc = (GLuint)glGetAttribLocation(shader.getId(), "inPosition");
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(positionLoc);
    GLuint textureLoc = (GLuint)glGetAttribLocation(shader.getId(), "inCoord");
    glVertexAttribPointer(textureLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(textureLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::startTouch(float x, float y) {
    startTouchPosition = glm::vec2{x, y};
}

void Engine::processTouch(float x, float y) {
    glm::vec2 delta = glm::vec2{x, y} - startTouchPosition;
    currentRotation = glm::vec3(delta.x, delta.y, 0.0f);
}

void Engine::createTexture(int width, int height, GLvoid *data) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}
