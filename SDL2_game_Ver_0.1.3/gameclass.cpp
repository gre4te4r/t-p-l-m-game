#include<SDL_image.h>
#include<SDL.h>

#include "gameclass.h"
#include"InputHandler.h"


Game::Game()
{
    myWindow = nullptr;
    myRenderer = nullptr;
    m_bRunning = false;
    m_currentFrame = 0;

}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags){

 if(SDL_Init(SDL_INIT_EVERYTHING) == 0){

    myWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    if(myWindow != 0){

        myRenderer = SDL_CreateRenderer(myWindow, -1, 0);

        if(myRenderer != 0){

            SDL_SetRenderDrawColor(myRenderer, 0,255,255,255);
            }
        else{
            return false;
            }
        }
    else{
        return false;
        }
 }
 else{
    return false;
    }

    IMG_Init(IMG_INIT_PNG||IMG_INIT_JPG);

    if(!TextureManager::Instance()->load("Run.png", "run", myRenderer)){
        return false;
    }
    if(!TextureManager::Instance()->load("Shot_1.png", "shot", myRenderer)){
        return false;
    }
    if(!TextureManager::Instance()->load("Idle.png", "idle", myRenderer)){
        return false;
    }

    player = new Player();
    player->load(300, 300, 128, 128, "run");
    m_gameObjects.push_back(player);

    if(!TextureManager::Instance()->load("Zombierun.png", "zombieRun", myRenderer)){
        return false;
    }

    if(!TextureManager::Instance()->load("Zombierun.png", "bullet", myRenderer)){
            std::cout << "er";
        return false;
    }

    bullet = new Bullet();
    bullet->load(300, 300, 96, 96, "bullet");

    if(!TextureManager::Instance()->load("Background.jpg", "background", myRenderer)){
        return false;
    }

    m_bRunning = true;
    return true;
}

void Game::render(){

    SDL_RenderClear(myRenderer);
//    TextureManager::Instance()->draw("background", 0, 0, 720, 480, myRenderer);

    player->draw(myRenderer);
    bullet->draw(myRenderer);

    for (std::vector<Enemy*>::size_type i = 0; i != m_enemies.size(); i++) {
        m_enemies[i]->draw(myRenderer);
    }



    for (std::vector<Bullet*>::size_type i = 0; i != bullets.size(); i++) {
        bullets[i]->draw(myRenderer);
    }



    SDL_RenderPresent(myRenderer);
}

void Game::update(){




    player->update();
    bullet->update();


    for(std::vector<GameObject*>::size_type i = 0; i != m_enemies.size(); i++){

        m_enemies[i]->update();

    }

    for(std::vector<GameObject*>::size_type i = 0; i != bullets.size(); i++){

        bullets[i]->update();

    }


}

void Game::handleEvents(){

    TheInputHandler::Instance()->update();
}

void Game::clean(){

    SDL_DestroyWindow(myWindow);
    SDL_DestroyRenderer(myRenderer);
    SDL_Quit();
}

void Game::spawnEnemy() {
    int ran = rand() % 2;
    int randomX;
    int randomY = rand() % (384 - 180 + 1) + 180;
    Enemy* newEnemy = new Enemy();

    if (ran == 1) {
        randomX = -100;
    } else {
        randomX = 800;
        newEnemy->flipEnemy();
    }

    newEnemy->load(randomX, randomY, 96, 96, "zombieRun");
    m_enemies.push_back(newEnemy);
}

void Game::generateBullet(){

    int ran = rand() % 2;
    int randomX;
    int randomY = rand() % (384 - 180 + 1) + 180;
    Bullet* newBullet = new Bullet();

    if (ran == 1) {
        randomX = 0;
    } else {
        randomX = 700;

    }

    newBullet->load(randomX, randomY, 96, 96, "bullet");
    bullets.push_back(newBullet);


}



