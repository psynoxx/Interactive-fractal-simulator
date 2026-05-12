#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.h"


class sierpinskiState : public gameState 
{
public:
    void init();

    void pause();
    void resume();
    void DrawTriangle(float size, sf::RenderWindow& Window, int depth, sf::Vector2f pos);

    void handleEvents(gameEngine& game);
    void update(gameEngine& game);
    void draw(gameEngine& game);

    static std::unique_ptr<gameState> instance(){ //static (limited to class) factory method //changed from std::unique_ptr<gameState> to std::unique_ptr<introState>
        return std::make_unique<sierpinskiState>();  // also of type 'gameState'
    } // we do this so each funtion can share a similar parent through which it is called



private:
    sf::Texture bgTexture;
    sf::RenderTexture sierText;
    float rt2;
    static sf::CircleShape triangle;
    sf::VertexArray sierpinski;


};