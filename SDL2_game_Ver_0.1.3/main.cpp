#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

#include "gameclass.h"

// our Game object
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
Uint32 lastSpawnTime = 0;
const Uint32 spawnInterval = 1000;

Game* g_game = 0;
int main(int argc, char* argv[])
{
 Uint32 frameStart, frameTime;
 g_game = new Game();
 g_game->init("SDL2game", 100, 100, 720, 480, 0);
 while(g_game->running())
 {
 frameStart = SDL_GetTicks();

 g_game->handleEvents();
 g_game->update();
 g_game->render();

 g_game->generateBullet();
 if (SDL_GetTicks() - lastSpawnTime >= spawnInterval) {
        g_game->spawnEnemy();

        lastSpawnTime = SDL_GetTicks();
    }





 frameTime = SDL_GetTicks() - frameStart;
 if(frameTime< DELAY_TIME)
 {
 SDL_Delay((int)(DELAY_TIME - frameTime));
 }
 }
 g_game->clean();
 return 0;
}
