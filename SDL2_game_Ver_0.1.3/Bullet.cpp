#include "Bullet.h"


void Bullet::load(int x, int y, int width, int height, std::string textureID){

    GameObject::load(x, y, width, height, textureID);

}

void Bullet::draw(SDL_Renderer* pRenderer){

    TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, pRenderer, m_flip);

}

void Bullet::update(){

}

bool Bullet::isOffScreen(){

        return m_position.getX() > 720;

}
