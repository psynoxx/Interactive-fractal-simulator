#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.h"


class menuState : public gameState 
{
public:
    void init();
    // void cleanup(); most likely unneeded

    void pause();
    void resume();

    void handleEvents(gameEngine& game);
    void update(gameEngine& game);
    void draw(gameEngine& game);

    void drawTriangle(float size,sf::RenderWindow& window, int depth, sf::Vector2f pos);

    static std::unique_ptr<gameState> instance(){ //static (limited to class) factory method //changed from std::unique_ptr<gameState> to std::unique_ptr<introState>
        return std::make_unique<menuState>();  // also of type 'gameState'
    } // we do this so each funtion can share a similar parent through which it is called
    

private:
    //std::unique_ptr<gameState> m_introState;
    sf::Texture bgTexture;


};
