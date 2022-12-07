#include "player.h"

Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
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
}

void Player::setDefault()
{
    Position = initialPos;
    cooldown = 0;
};

void Player::moveLeft(float dt)
{
    Position.x -= Velocity.x * dt;
};

void Player::moveRight(float dt)
{
    Position.x += Velocity.x * dt;
}

void Player::lowerCooldown(float dt)
{
    if (cooldown > 0)
    {
        cooldown -= dt * 50;
    }
}

bool Player::shoot(Enemy* other)
{
    if (cooldown <= 0)
    {
        cooldown = cooldownLength;
        float playerCenter = Position.x + (Size.x / 2);
        if (playerCenter > other->Position.x && playerCenter < other->Position.x + other->Size.x)
        {
            if (!other->Destroyed && cooldown <= 0)
            {
                other->Destroyed = true;
                return true;
            }
        }
    }
    return false;
}