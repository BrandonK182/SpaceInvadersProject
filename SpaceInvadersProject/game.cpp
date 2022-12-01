#include "game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

#include <iostream>

// Game-related State data
SpriteRenderer* Renderer;
GameObject* Player;
GameObject* Enemy;
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const glm::vec2 ENEMY_SIZE(75.0f, 75.0f);
const float PLAYER_VELOCITY(500.0f);
const static int numRows = 10;
const static int numCols = 3;
float timer = 500;
int direction = 2;
//1 = left
//2 = right
//3 = down heading left
//4 = down heading right
bool enemies[numRows][numCols];

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    //sets all values to empty
    for (int row = 0; row < 15; row++)
    {
        for (int col = 0; col < 12; col++)
        {
            enemies[row][col] = 0;
        }
    }

    // load shaders
    ResourceManager::LoadShader("core.vs", "core.frag", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader shade = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shade);
    // load textures
    ResourceManager::LoadTexture("textures/zoro.png", true, "enemy");
    ResourceManager::LoadTexture("textures/trainer.png", true, "player");

    level.Load("level.lvl", this->Width, this->Height / 2);


    glm::vec2 playerPos = glm::vec2(
        this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
        this->Height - PLAYER_SIZE.y
    );
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"));

    glm::vec2 enemyPos = glm::vec2(
        0.0f,
        this->Height -600.0f
    );
    Enemy = new GameObject(enemyPos, ENEMY_SIZE, ResourceManager::GetTexture("enemy"));
}

void Game::Update(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        switch(direction)
        {
        case 1:
            Enemy->Position.x -= dt * 50;
            if (timer < 0)
            {
                direction = 4;
                timer = 20;
            }
            break;
        case 2:
            Enemy->Position.x += dt * 50;
            if (timer < 0)
            {
                direction = 3;
                timer = 20;
            }
            break;
        case 3:
            Enemy->Position.y += dt * 100;
            if (timer < 0)
            {
                direction = 1;
                timer = 500;
            }
            break;
        case 4:
            Enemy->Position.y += dt * 100;
            if (timer < 0)
            {
                direction = 2;
                timer = 500;
            }
            break;
        }
        timer -= dt * 50;
        
    }
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0.0f)
                Player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
                Player->Position.x += velocity;
        }
    }
}

void Game::Render()
{
    Texture2D myTexture;
    myTexture = ResourceManager::GetTexture("player");
    myTexture = ResourceManager::GetTexture("enemy");
    Player->Draw(*Renderer);
    Enemy->Draw(*Renderer);
}