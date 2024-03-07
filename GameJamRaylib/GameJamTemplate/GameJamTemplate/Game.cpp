#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "EnvironmentBlock.h"
#include "Watermelon.h"
#include "Enemy.h"

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

    m_gameState = 0;
    m_spawnTimer = 1;
    m_spawnDelay = m_spawnDelayDefault;
    m_minSpawnDelay = 0.5;

    m_gameTRCorner = { 200, -375 };
    m_gameBLCorner = { -200, 375 };

    m_currentFallSpeed = m_startingFallSpeed;
    m_roundTimer = 20;
    bordersOn = true;
    cursorRect = { 0,0,0,0 };
    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    HideCursor();

}

void Game::Unload()
{
    delete m_root;
    delete m_player;
}

void Game::Update(float deltaTime)
{
    m_root->Update(deltaTime);




    if (m_gameState == 0) {
      
        m_roundTimer -= deltaTime;
        if (m_roundTimer <= 0) {
            m_gameState = 1;          
        }
        
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
    }

    if (m_gameState == 1) {
        
        if (m_gameBLCorner.x >= m_screenTLCorner.x) 
        {
            m_gameBLCorner.x -= 110 * deltaTime;
        }
        else {
            m_gameBLCorner.x = m_screenTLCorner.x;
            bordersOn = false;
        }

        if (m_gameTRCorner.x <= m_screenBRCorner.x)
        {
            m_gameTRCorner.x += 110 * deltaTime;
        }
        else {
            m_gameTRCorner.x = m_screenBRCorner.x;
            bordersOn = false;
        }


        if (m_player->GetPos().x == -15 && m_player->GetPos().y == -15) {
            m_gameState = 2;
            m_roundTimer = 0;

            m_delayDecreaseTimer = 0;
            m_spawnDelay = m_spawnDelayDefault;
            m_minSpawnDelay = 1;

            cursorRect = { 0,0,20,20 };
         
            ShowCursor();

            bordersOn = false;
        }

        else if (!m_player->GetLerping()) {
            m_player->LerpTo({ 0 - m_player->GetGameRect().width / 2, 0 - m_player->GetGameRect().height / 2 }, 4);
        }
    
      


    }

    if (m_gameState == 2) {
        m_roundTimer += deltaTime;


        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            std::cout << "CLICKED" << std::endl;
            for (GameObject* go : m_root->children)
            {
                Enemy* e = dynamic_cast<Enemy*>(go);
                //EnvironmentBlock* eb = dynamic_cast<EnvironmentBlock*>(go);
                //Dont want player to check collision with itself :x
                if (e != nullptr)
                {

                    if (CheckCollisionPointRec({ GetMouseX() - m_camera.offset.x, GetMouseY() - m_camera.offset.y }, go->GetGameRect()))
                    {
                        //For each melon you hit, add to your seed counter. 
                        //YOU START WITH NOTHING WOW
                         //m_game->m_root->children.erase(std::remove(m_game->m_root->children.begin(), m_game->m_root->children.end(), go));
                        std::cout << "CLICKED AN ENEMY" << std::endl;
                        delete e;
                        m_root->children.erase(std::remove(m_root->children.begin(), m_root->children.end(), e));
                        break;
                    }
                }
            }
        }


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


            float spawnY = (rand() % (int)(m_windowWidth)) + 1;
            bool left = rand() % 2;
            float spawnX = 0;
            if (left) { spawnX = -650; }
            else { spawnX = 650; }


            m_root->AddChild(new Enemy({ spawnX, spawnY }, { 25, 25 }, this));
            m_root->AddChild(new Enemy({ 0, 0 }, { 25, 25 }, this));

        }




    }

    //Camera follow player directly
    //m_camera.target = m_player->GetPos();
}

void Game::Draw()
{
	BeginMode2D(m_camera); //Function for using the 2D camera "camera" thats been created
	ClearBackground(SKYBLUE);

    m_root->Draw();


    // DrawRectangle(0, 100, 500, 500, GRAY);
    if (bordersOn) {
        DrawRectangle(m_screenTLCorner.x, m_screenTLCorner.y, abs(m_screenTLCorner.x - m_gameBLCorner.x), m_windowHeight, GRAY);
        DrawRectangle(m_gameTRCorner.x, m_gameTRCorner.y, abs(m_screenBRCorner.x - m_gameTRCorner.x), m_windowHeight, GRAY);
    }

    switch (m_gameState) {
        case 2: {
            
        }
    }

    EndMode2D();

	DrawFPS(10, 10);
    DrawText(seedCountUI.CStr(), 10, 40, 20, WHITE);
    DrawText(String::IntToString(m_currentFallSpeed).CStr(), 10, 70, 20, WHITE);
    DrawText(String::IntToString(m_spawnDelay).CStr(), 10, 100, 20, WHITE);
    DrawText(String::IntToString(m_roundTimer).CStr(), 590, 50, 40, BLACK);

    DrawText(String::IntToString(GetMouseX()).CStr(), 10, 120, 20, WHITE);
    DrawText(String::IntToString(GetMouseY()).CStr(), 10, 140, 20, WHITE);
    DrawText(String::IntToString(m_camera.offset.x).CStr(), 10, 160, 20, WHITE);
    DrawText(String::IntToString(m_camera.offset.y).CStr(), 10, 180, 20, WHITE);


	EndDrawing();
}

void Game::ResetSpawnDelay() {
    m_spawnDelay = m_spawnDelayDefault;
}

void Game::ResetFallSpeed() {
    m_currentFallSpeed = m_startingFallSpeed;
}

