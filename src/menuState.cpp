#include <SFML/Graphics.hpp>
#include <iostream>
#include "menuState.h"
#include "gameState.h"
#include "gameEngine.h"
#include "playState.h"


void menuState::init(){
    if (!bgTexture.loadFromFile("menu.bmp", false, sf::IntRect({0, 0}, {1920, 1080})))
    {
        std::cout << ("failed to load bg from file");
        //game.quit
    }

    //implement alpha channel if time

}

void menuState::pause(){
    std::cout << ("menuState paused") << std::endl;
}

void menuState::resume(){
    std::cout << ("menuState resumed") << std::endl;
}

void menuState::handleEvents(gameEngine& game){
    while (const std::optional event = game.window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            game.quit();
        }
        else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                game.pushState(playState::instance());
            }

        }
    }
}

void menuState::update(gameEngine& game){
    //update
}

void menuState::draw(gameEngine& game){
    sf::Sprite bgSprite(bgTexture);
    game.window.draw(bgSprite);
}