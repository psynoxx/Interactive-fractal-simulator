#include <SFML/Graphics.hpp>
#include <iostream>
#include "menuState.h"
#include "gameState.h"
#include "gameEngine.h"
#include "playState.h"
#include "sierpinskiState.h"

sf::Font mfont;
sf::Text mtext(mfont);
float rt3m = 1.73205080757;

void menuState::init(){

    showUI = false;

    if (!bgTexture.loadFromFile("menu.bmp", false, sf::IntRect({0, 0}, {1920, 1080})))
    {
        std::cout << ("failed to load bg from file");
        //game.quit
    }
    if(!mfont.openFromFile("minecraft.ttf")){
        std::cout << ("failed to load font");
    }
    mtext.setFont(mfont);
    mtext.setString("intro state");
    mtext.setCharacterSize(50);
    mtext.setPosition({1920/2 -mtext.getLocalBounds().size.x/2,1080/2 -mtext.getLocalBounds().size.y/2});

    //implement alpha channel if time

}

void menuState::pause(){
    std::cout << ("menuState paused") << std::endl;
}

void menuState::resume(){
    std::cout << ("menuState resumed") << std::endl;
}

void menuState::drawTriangle(float size,sf::RenderWindow& window, int depth, sf::Vector2f pos){
    sf::CircleShape triangle(size,3);
    triangle.setOrigin(triangle.getGeometricCenter());
    triangle.setPosition(pos);
    sf::CircleShape sub1(size/2,3);
    sub1.setOrigin(sub1.getGeometricCenter());
    sub1.setPosition({triangle.getPosition().x,triangle.getPosition().y + size});
    sf::CircleShape sub2(size/2,3);
    sub2.setOrigin(sub2.getGeometricCenter());
    sub2.setPosition({triangle.getPosition().x+rt3m*(size)/2, triangle.getPosition().y-size/2});
    sf::CircleShape sub3(size/2,3);
    sub3.setOrigin(sub3.getGeometricCenter());
    sub3.setPosition({triangle.getPosition().x-rt3m*size/2, triangle.getPosition().y-size/2});

    window.draw(triangle);
    window.draw(sub1);
    window.draw(sub2);
    window.draw(sub3);

};

void menuState::handleEvents(gameEngine& game){
    while (const std::optional event = game.window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            game.quit();
        }
        else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
            if(keyPressed->scancode == sf::Keyboard::Scancode::Q){
                game.changeState(sierpinskiState::instance());
            }
            if(keyPressed->scancode == sf::Keyboard::Scancode::W){
                game.pushState(sierpinskiState::instance());
            }
            if(keyPressed->scancode == sf::Keyboard::Scancode::E){
                game.popState();
            }

        }
    }
}

void menuState::update(gameEngine& game){
    //update
}

void menuState::draw(gameEngine& game){
    sf::Sprite bgSprite(bgTexture);
    //game.window.draw(bgSprite);
    //game.window.draw(mtext);
    drawTriangle(200,game.window,1,{static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
}