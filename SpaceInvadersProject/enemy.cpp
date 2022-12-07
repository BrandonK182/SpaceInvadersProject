#include "enemy.h"

Enemy::Enemy(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
{
    Position = pos;
    initialPos = pos;
    Size = size;
    Velocity = velocity;
    Color = color;
    Rotation = 0.0f;
    Sprite = sprite;
    IsSolid = false;
    Destroyed = false;
    direction = 2;
    timer = 333;
};

void Enemy::setDefault()
{
    Position = initialPos;
    Destroyed = false;
    direction = 2;
    timer = 333;
};

void Enemy::move(float dt)
{
    switch (direction)
    {
    case 1: // enemies move left
        moveLeft(dt);
        if (timer < 0)
        {
            setDownRight();
            timer = 20;
        }
        break;
    case 2: // enemies move right
        moveRight(dt); // dt * # -> # default 50
        if (timer < 0)
        {
            setDownLeft(); // dt * # -> # default 50
            timer = 20;
        }
        break;
    case 3: // enemies move down then left
        moveDown(dt);
        if (timer < 0)
        {
            setLeft();
            timer = 400; // timer = # -> # default 500
        }
        break;
    case 4: // enemies move down then right
        moveDown(dt);
        if (timer < 0)
        {
            setRight();
            timer = 400; // timer = # -> # default 500
        }
        break;
    }
    timer -= dt * 50;
};

void Enemy::moveLeft(float dt)
{
    Position.x -= dt * 75; // dt * # -> # default 50
};

void Enemy::moveRight(float dt)
{
    Position.x += dt * 75;
};

void Enemy::moveDown(float dt)
{
    Position.y += dt * 200;
};

void Enemy::setLeft() 
{
    direction = 1;
};

void Enemy::setRight() 
{
    direction = 2;
};

void Enemy::setDownLeft() 
{
    direction = 3;
};

void Enemy::setDownRight() 
{ 
    direction = 4; 
};

void Enemy::destroy()
{
    Destroyed = true;
};