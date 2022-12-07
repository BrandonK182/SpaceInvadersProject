#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"

class Enemy : public GameObject
{
public:
    Enemy(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    glm::vec2 initialPos;
	int direction;
    float timer;
    void setDefault();
	void move(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);
	void moveDown(float dt);
	void setLeft();
	void setRight();
	void setDownLeft();
	void setDownRight();
};

#endif

