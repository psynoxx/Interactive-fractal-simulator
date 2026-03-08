#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.h"


class playState : public gameState 
{
public:
    void init();
    // void cleanup(); most likely unneeded

    void pause();
    void resume();

    void handleEvents(gameEngine& game);
    void update(gameEngine& game);
    void draw(gameEngine& game);

    static std::unique_ptr<gameState> instance(){ //static (limited to class) factory method //changed from std::unique_ptr<gameState> to std::unique_ptr<introState>
        return std::make_unique<playState>();  // also of type 'gameState'
    } // we do this so each funtion can share a similar parent through which it is called


private:
    sf::Texture bgTexture;
    sf::RenderTexture renderTexture;
    static sf::CircleShape b_triangle;
    static sf::CircleShape s1_triangle;

};

//translate to playState