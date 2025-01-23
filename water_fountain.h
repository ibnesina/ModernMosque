#ifndef WATER_FOUNTAIN_H
#define WATER_FOUNTAIN_H

#include <vector>
#include <glm/glm.hpp>
#include "shader.h"

struct WaterParticle {
    glm::vec3 position;
    glm::vec3 velocity;
    float lifetime;
    
};

class WaterFountain {
public:
    glm::vec3 sourcePosition;
    std::vector<WaterParticle> particles;
    int maxParticles;
    float gravity;
    unsigned int sphereVAO, sphereVBO, sphereEBO;

    WaterFountain(glm::vec3 source, int maxParticles = 2000, float gravity = 9.8f);
    ~WaterFountain();
    
    void update(float deltaTime);
    void render(Shader &shader);
    void setupSphere();
    void drawSphere();
};

#endif
