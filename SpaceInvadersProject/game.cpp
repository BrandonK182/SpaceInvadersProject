#include "game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

#include <iostream>
#include <vector>

// Game-related State data
SpriteRenderer* Renderer;
GameObject* Player;
GameObject* Enemy;
GameObject* winScreen;
GameObject* loseScreen;
std::vector<GameObject*> enemies;
const glm::vec2 PLAYER_SIZE(100.0f, 75.0f); // const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const glm::vec2 ENEMY_SIZE(75.0f, 75.0f);
const glm::vec2 WINSCREEN_SIZE(800.0f, 600.0f);
const glm::vec2 LOSESCREEN_SIZE(800.0f, 600.0f);
const float PLAYER_VELOCITY(500.0f);
const static int numRows = 10;
const static int numCols = 10;
const static int numEnemiesPerRow = 4;
const static int numEnemyRows = 3;
static int remaining = numEnemiesPerRow * numEnemyRows;
const static float cooldownLength = 25;
float cooldown = 0;
float timer = 50; // timer = # -> # default 500
int direction = 2;
//1 = left
//2 = right
//3 = down heading left
//4 = down heading right
int playerLives = 1;
bool enemiesAlive[numRows][numCols];

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
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            enemiesAlive[row][col] = 0;
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
    ResourceManager::LoadTexture("textures/winscreen.png", true, "enemy"); //("textures/zoro.png", true, "enemy")
    ResourceManager::LoadTexture("textures/winscreen.png", true, "player"); //("textures/trainer.png", true, "player")
    ResourceManager::LoadTexture("textures/winscreen.png", true, "winscreen");
    ResourceManager::LoadTexture("textures/losescreen.png", true, "losescreen");


    level.Load("level.lvl", this->Width, this->Height / 2);

    // player model
    glm::vec2 playerPos = glm::vec2(
        this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
        this->Height - PLAYER_SIZE.y
    );
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"));

    // enemy model
    glm::vec2 enemyPos = glm::vec2(
        0.0f,
        this->Height - 600.0f
    );
    for (int i = 0; i < numEnemyRows; i++)
    {
        for (int j = 0; j < numEnemiesPerRow; j++)
        {
            enemies.push_back(new GameObject(enemyPos, ENEMY_SIZE, ResourceManager::GetTexture("enemy")));
            enemyPos.x += ENEMY_SIZE.x;
        }
        enemyPos.x = 0.0f;
        enemyPos.y += ENEMY_SIZE.y;
    }

    // winscreen model
    glm::vec2 winScreenPos = glm::vec2(
        this->Width - WINSCREEN_SIZE.x,
        this->Height - WINSCREEN_SIZE.y
    );
    winScreen = new GameObject(winScreenPos, WINSCREEN_SIZE, ResourceManager::GetTexture("winscreen"));

    // losescreen model
    glm::vec2 loseScreenPos = glm::vec2(
        this->Width - LOSESCREEN_SIZE.x,
        this->Height - LOSESCREEN_SIZE.y
    );
    loseScreen = new GameObject(winScreenPos, LOSESCREEN_SIZE, ResourceManager::GetTexture("losescreen"));
}

void Game::Update(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        switch (direction)
        {
        case 1: // enemies move left
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i]->Position.x -= dt * 50; // dt * # -> # default 50
            }
            if (timer < 0)
            {
                direction = 4;
                timer = 20;
            }
            break;
        case 2: // enemies move right
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i]->Position.x += dt * 50; // dt * # -> # default 50
            }
            if (timer < 0)
            {
                direction = 3;
                timer = 20;
            }
            break;
        case 3: // enemies move down then left
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i]->Position.y += dt * 200;
            }
            if (timer < 0)
            {
                direction = 1;
                timer = 100; // timer = # -> # default 500
            }
            break;
        case 4: // enemies move down then right
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i]->Position.y += dt * 200;
            }
            if (timer < 0)
            {
                direction = 2;
                timer = 100; // timer = # -> # default 500
            }
            break;
        }
        timer -= dt * 50;
        if (cooldown > 0)
        {
            cooldown -= dt * 50;
        }

        // if all enemies are dead, gamestate -> win
        if (remaining <= 0)
        {
            this->State = GAME_WIN;
            std::cout << "winscreen" << std::endl; //
        }

        // if enemies touch player, automatically lose
        float playerLeft = Player->Position.x;
        float playerRight = Player->Position.x + PLAYER_SIZE.x;
        float playerTop = Player->Position.y;
        //float enemyLeft = enemies[i]->Position.x;
        //float enemyRight = enemies[i]->Position.x + ENEMY_SIZE.x;
        //float enemyBot = enemies[i]->Position.y + ENEMY_SIZE.y;
        bool sameLevel = false; //bool sameLevel = false;
        for (int i = 0; i < enemies.size(); i++)
        {
            //std::cout << playerTop << std::endl; // == 525
            //std::cout << enemies[i]->Position.y + (numEnemyRows - 1) * ENEMY_SIZE.y << std::endl; //
            if (playerTop <= enemies[i]->Position.y + ENEMY_SIZE.y)
            {
                sameLevel = true;
                std::cout << "sameLevel true" << std::endl; //
            }
        }
        if (sameLevel == true)
        {
            for (int i = 0; i <= enemies.size() - 1; i++)
            {
                std::cout << playerTop << std::endl;
                std::cout << enemies[i]->Position.y + ENEMY_SIZE.y << std::endl;
                if (playerLeft >= enemies[i]->Position.x && playerLeft <= enemies[i]->Position.x + ENEMY_SIZE.x // if left edge is inside an enemy
                    || playerRight >= enemies[i]->Position.x && playerRight <= enemies[i]->Position.x + ENEMY_SIZE.x) // or if right edge ^^^
                {
                    if (playerTop <= enemies[i]->Position.y + ENEMY_SIZE.y) // and top edge is past an enemy
                    {
                        if (!enemies[i]->Destroyed)
                        {
                            std::cout << "colliding" << std::endl; //
                            this->State = GAME_LOSE;
                        }
                    }
                }
            }
            std::cout << std::endl;
        }


        if (playerLives <= 0)
        {
            this->State = GAME_LOSE;
            std::cout << "losescreen" << std::endl; //
        }
    }
    if (this->State == GAME_ACTIVE)
    {

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
        if (this->Keys[GLFW_KEY_SPACE])
        {
            float playerCenter = Player->Position.x + (PLAYER_SIZE.x / 2);
            bool contact = false;
            for (int i = enemies.size() - 1; i >= 0; i--)
            {
                if (playerCenter > enemies[i]->Position.x && playerCenter < enemies[i]->Position.x + ENEMY_SIZE.x)
                {
                    if (!enemies[i]->Destroyed && !contact && cooldown <= 0)
                    {
                        enemies[i]->Destroyed = true;
                        remaining -= 1;
                        contact = true;
                        i = -1;
                    }
                }
            }
            if (cooldown <= 0)
                cooldown = cooldownLength;
        }
    }
    if (this->State == GAME_WIN)
    {
        if (this->Keys[GLFW_KEY_ENTER])
        {
            this->State = GAME_ACTIVE;
            remaining = numEnemiesPerRow * numEnemyRows;
            cooldown = 0;
            timer = 500;
            direction = 2;
            playerLives = 1;
            glm::vec2 enemyPos = glm::vec2(
                0.0f,
                this->Height - 600.0f
            );
            int itr = 0;
            for (int i = 0; i < numEnemyRows; i++)
            {
                for (int j = 0; j < numEnemiesPerRow; j++)
                {
                    enemies[itr]->Position = enemyPos;
                    enemies[itr]->Destroyed = false;
                    enemyPos.x += ENEMY_SIZE.x;
                    itr++;
                }
                enemyPos.x = 0.0f;
                enemyPos.y += 50.0f;
            }
        }
    }
    if (this->State == GAME_LOSE)
    {
        if (this->Keys[GLFW_KEY_ENTER])
        {
            this->State = GAME_ACTIVE;
        }
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        Player->Draw(*Renderer);
        for (int i = 0; i < enemies.size(); i++)
        {
            if (!enemies[i]->Destroyed)
                enemies[i]->Draw(*Renderer);
        }
    }
    if (this->State == GAME_WIN)
    {
        winScreen->Draw(*Renderer);
    }
    if (this->State == GAME_LOSE)
    {
        loseScreen->Draw(*Renderer);
    }
}