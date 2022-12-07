#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
#include "enemy.h"

class Player : public GameObject
{
public:
    Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(200.0f, 0.0f));
    glm::vec2 initialPos;
    float cooldown = 0;
    float cooldownLength = 25;
    void setDefault();
    void moveLeft(float dt);
    void moveRight(float dt);
    void lowerCooldown(float dt);
    bool shoot(Enemy* other);
    void setCooldown();
};


#endif
