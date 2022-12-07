#include "GameObject.h"

GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false) { }

bool GameObject::collidedWith(GameObject other)
{
    float otherX = other.Position.x;
    float otherY = other.Position.y;
    float otherSizeX = other.Size.x;
    float otherSizeY = other.Size.y;
    if ((Position.x >= otherX && Position.x <= otherX + otherSizeX) // if left edge is in an enemy
        || (Position.x + Size.x >= otherX && Position.x + Size.x <= otherX + otherSizeX)) // or if right edge is ^^^
    {
        if (Position.y <= otherY + otherSizeY) // and top edge is past an enemy's bottom
        {
            return true;
        }
    }
    return false;
}

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}