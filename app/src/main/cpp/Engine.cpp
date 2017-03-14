#include "Engine.h"

void Engine::init(int width, int height) {
    this->width = width;
    this->height = height;
    shader.createProgram();
    createVertexBuffer();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void Engine::draw() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader.getId());
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glm::mat4 model;
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(-1.0f, 1.0f, 0.0f));

    glm::mat4 view;
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

    float aspectRatio = (float)width / (float)height;
    glm::mat4 projection;
    projection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);


    GLint modelLoc = glGetUniformLocation(shader.getId(), "model");
    GLint viewLoc = glGetUniformLocation(shader.getId(), "view");
    GLint projectionLoc = glGetUniformLocation(shader.getId(), "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::createVertexBuffer() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    auto x = sizeof(vertices);

    GLuint positionLoc = (GLuint)glGetAttribLocation(shader.getId(), "inPosition");
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(positionLoc);
    GLuint textureLoc = (GLuint)glGetAttribLocation(shader.getId(), "inCoord");
    glVertexAttribPointer(textureLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(textureLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
