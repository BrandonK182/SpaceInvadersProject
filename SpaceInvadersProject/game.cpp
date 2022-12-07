#include "game.h"

// Game-related State data
SpriteRenderer* Renderer;
Player* thePlayer;
GameObject* winScreen;
GameObject* loseScreen;
std::vector<Enemy*> enemies;
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
float defaultHorizontal = 333;
float timer = defaultHorizontal; // timer = # -> # default 500
int direction = 2;
//1 = left
//2 = right
//3 = down heading left
//4 = down heading right
int playerLives = 1;

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
    ResourceManager::LoadTexture("textures/zoro.png", true, "enemy"); //("textures/zoro.png", true, "enemy")
    ResourceManager::LoadTexture("textures/trainer.png", true, "player"); //("textures/trainer.png", true, "player")
    ResourceManager::LoadTexture("textures/winscreen.png", true, "winscreen");
    ResourceManager::LoadTexture("textures/losescreen.png", true, "losescreen");

    // player model
    glm::vec2 playerPos = glm::vec2(
        this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
        this->Height - PLAYER_SIZE.y
    );
    thePlayer = new Player(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"));

    // enemy model
    glm::vec2 enemyPos = glm::vec2(
        0.0f,
        this->Height - 600.0f
    );
    for (int i = 0; i < numEnemyRows; i++)
    {
        for (int j = 0; j < numEnemiesPerRow; j++)
        {
            enemies.push_back(new Enemy(enemyPos, ENEMY_SIZE, ResourceManager::GetTexture("enemy")));
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
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->move(dt);
        }

        thePlayer->lowerCooldown(dt);

        // if all enemies are dead, gamestate -> win
        if (remaining <= 0)
        {
            this->State = GAME_WIN;
            std::cout << "winscreen" << std::endl; //
        }

        // if enemies touch player, automatically lose
        {
            for (int i = 0; i <= enemies.size() - 1; i++)
            {
                if (!enemies[i]->Destroyed) // if enemy isnt destroyed
                {
                    if (enemies[i]->Position.y >= Height) // if enemy leaves screen
                    {
                        std::cout << "passed you" << std::endl; //
                        this->State = GAME_LOSE;
                    }
                    if (thePlayer->collidedWith(*enemies[i]))
                    {
                        std::cout << "colliding" << std::endl; //
                        this->State = GAME_LOSE;
                    }
                }
            }
        }

        //lose if no lives
        if (playerLives <= 0)
        {
            this->State = GAME_LOSE;
            std::cout << "losescreen" << std::endl; //
        }
    }

}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (thePlayer->Position.x >= 0.0f)
                thePlayer->moveLeft(dt);
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (thePlayer->Position.x <= this->Width - thePlayer->Size.x)
                thePlayer->moveRight(dt);
        }
        if (this->Keys[GLFW_KEY_SPACE])
        {
            bool contact = false;
            for (int i = enemies.size() - 1; i >= 0; i--)
            {
                if (!contact)
                    contact = thePlayer->shoot(enemies[i]);
            }
        }
    }
    if (this->State == GAME_LOSE || this->State == GAME_WIN)
    {
        if (this->Keys[GLFW_KEY_ENTER])
        {
            this->State = GAME_ACTIVE;
            remaining = numEnemiesPerRow * numEnemyRows;
            cooldown = 0;
            playerLives = 1;
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i]->setDefault();
            }
            thePlayer->setDefault();
        }
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        thePlayer->Draw(*Renderer);
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