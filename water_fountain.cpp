#include "water_fountain.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

WaterFountain::WaterFountain(glm::vec3 source, int maxParticles, float gravity) 
    : sourcePosition(source), maxParticles(maxParticles), gravity(gravity), sphereVAO(0), sphereVBO(0), sphereEBO(0) {
    particles.resize(maxParticles);
}

WaterFountain::~WaterFountain() {
    glDeleteVertexArrays(1, &sphereVAO);
    glDeleteBuffers(1, &sphereVBO);
    glDeleteBuffers(1, &sphereEBO);
}

void WaterFountain::update(float deltaTime) {
    for (auto &particle : particles) {
        particle.velocity.y -= gravity * deltaTime; // Apply gravity
        particle.position += particle.velocity * deltaTime;
        particle.lifetime -= deltaTime;

        if (particle.lifetime <= 0.0f) {
            particle.position = sourcePosition;
            particle.velocity = glm::vec3((rand() % 20 - 10) * 0.2f, 5.0f, (rand() % 20 - 10) * 0.2f);
            particle.lifetime = (rand() % 100 + 50) / 50.0f;
        }
    }
}

void WaterFountain::render(Shader &shader) {
    static bool initialized = false;
    if (!initialized) {
        std::cout << "Initializing sphere inside render()" << std::endl;
        setupSphere();
        initialized = true;
    }

    shader.use();

    for (const auto &particle : particles) {
        if (particle.lifetime > 0.0f) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, particle.position);
            model = glm::scale(model, glm::vec3(0.2f));  

            shader.setMat4("model", model);
            drawSphere();
        }
    }
}

void WaterFountain::setupSphere() {
    if (glGetError() != GL_NO_ERROR) {
        std::cerr << "Error: OpenGL context is NOT active before glGenVertexArrays!" << std::endl;
        return;
    }

    std::cout << "Creating Sphere VAO..." << std::endl;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int sectorCount = 20, stackCount = 20;
    float radius = 0.05f;
    float x, y, z, xy;
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        y = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;
            x = xy * cosf(sectorAngle);
            z = xy * sinf(sectorAngle);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            float length = sqrt(x * x + y * y + z * z);
            vertices.push_back(x / length);
            vertices.push_back(y / length);
            vertices.push_back(z / length);
        }
    }

    int k1, k2;
    for (int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glGenBuffers(1, &sphereEBO);

    if (sphereVAO == 0 || sphereVBO == 0 || sphereEBO == 0) {
        std::cerr << "Error: VAO/VBO/EBO creation failed!" << std::endl;
        return;
    }

    glBindVertexArray(sphereVAO);

    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
}

void WaterFountain::drawSphere() {
    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLES, 20 * 20 * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
