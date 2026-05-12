#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.h"


class treeState : public gameState 
{
public:
    void init();

    void pause();
    void resume();
    void DrawTree(float size, float angle, sf::RenderWindow& window, int depth, sf::Vector2f point);
    
    void handleEvents(gameEngine& game);
    void update(gameEngine& game);
    void draw(gameEngine& game);

    static std::unique_ptr<gameState> instance(){ //static (limited to class) factory method //changed from std::unique_ptr<gameState> to std::unique_ptr<introState>
        return std::make_unique<treeState>();  // also of type 'gameState'
    } // we do this so each funtion can share a similar parent through which it is called

    

private:

};