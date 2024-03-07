#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "EnvironmentBlock.h"
#include "Watermelon.h"

Game::Game()
{
	//Default constructor
}

Game::~Game()
{
	//Destructor
}

void Game::Run()
{
	//Contains raylib window launching and game logic loop calls
    InitWindow(m_windowWidth, m_windowHeight, "Raylib Template");

    SetTargetFPS(60);

    Load();

    while (!WindowShouldClose())
    {
        Update(GetFrameTime());
        Draw();
    }

    Unload();

    CloseWindow();

}

void Game::Load()
{
    m_root = new GameObject();
    m_player = new Player({0, 250}, {30, 30}, this);

    //Add player to game logic
    m_root->AddChild(m_player);
    

    //m_root->AddChild(new Watermelon({ -50, 150 }, { 30, 30 }, this));
   
    //SetUp Camera
    m_camera.offset = { (float)m_windowWidth / 2, (float)m_windowHeight / 2 };
    m_camera.rotation = 0.0f;
    m_camera.zoom = 1.0f;

    srand(time(NULL));
}

void Game::Unload()
{
    delete m_root;
    delete m_player;
}

void Game::Update(float deltaTime)
{
    m_root->Update(deltaTime);

    seedCountUI = String::IntToString(m_player->GetSeedCount());

    if (m_delayDecreaseTimer > 0) {
        m_delayDecreaseTimer -= deltaTime;
    }
    else {
        m_delayDecreaseTimer = 3;
        if (m_spawnDelay > m_minSpawnDelay) m_spawnDelay -= 0.5f;
        else if (m_spawnDelay < m_minSpawnDelay) m_spawnDelay = m_minSpawnDelay;


        if (m_currentFallSpeed < m_maxFallSpeed) m_currentFallSpeed += 50;
    }


    if (m_spawnTimer > 0) {
        m_spawnTimer -= deltaTime;
    }
    else {
        m_spawnTimer = m_spawnDelay;


        float spawnPos = (rand() % (int)(m_spawnableRange.y)) + 1;
        m_root->AddChild(new Watermelon({ m_spawnableRange.x + spawnPos, -400 }, { 50, 50 }, this, m_currentFallSpeed));
    }


    

    //Camera follow player directly
    //m_camera.target = m_player->GetPos();
}

void Game::Draw()
{
	BeginMode2D(m_camera); //Function for using the 2D camera "camera" thats been created
	ClearBackground(BLACK);

    m_root->Draw();


    // DrawRectangle(0, 100, 500, 500, GRAY);

    DrawRectangle(m_screenTLCorner.x, m_screenTLCorner.y, 400, m_windowHeight, GRAY);
    DrawRectangle(m_gameTRCorner.x, m_gameTRCorner.y, 400, m_windowHeight, GRAY);


    EndMode2D();

	DrawFPS(10, 10);
    DrawText(seedCountUI.CStr(), 10, 40, 20, WHITE);
    DrawText(String::IntToString(m_currentFallSpeed).CStr(), 10, 70, 20, WHITE);
    DrawText(String::IntToString(m_spawnDelay).CStr(), 10, 100, 20, WHITE);



	EndDrawing();
}

void Game::ResetSpawnDelay() {
    m_spawnDelay = m_spawnDelayDefault;
}

void Game::ResetFallSpeed() {
    m_currentFallSpeed = m_startingFallSpeed;
}

