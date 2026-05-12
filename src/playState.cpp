#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>
#include "playState.h"
#include "menuState.h"
#include "gameState.h"
#include "gameEngine.h"
#include "sierpinskiState.h"
#include "treeState.h"
#include "kochState.h"

sf::CircleShape playState::b_triangle(100.f,3);
sf::CircleShape playState::s1_triangle(50.f,3);
sf::RectangleShape sRect({640-200-300,540-100});
sf::Font f;
sf::Text pos(f);
sf::Clock fader;
sf::View view1(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));


float b = 0;
float s = 1;
float t = 1;
float k = 1;

void playState::init(){

    showUI = false;
    
    if (!Sier.loadFromFile("Sier.png", false, sf::IntRect({0, 0}, {1920, 1080})))
    {
        std::cout << ("failed to load bg from file");
        //game.quit
    }
    if (!Tree.loadFromFile("Tree.png", false, sf::IntRect({0, 0}, {1920, 1080})))
    {
        std::cout << ("failed to load bg from file");
        //game.quit
    }
    if (!Koch.loadFromFile("Koch.png", false, sf::IntRect({0, 0}, {1920, 1080})))
    {
        std::cout << ("failed to load bg from file");
        //game.quit
    }

    sRect.setFillColor(sf::Color::White);
    if(!f.openFromFile("Minecraft.ttf")){
        return;
    };
    pos.setFont(f);
    fader.start();    
    
    
    //implement alpha channel if time

}

void playState::pause(){
    std::cout << ("playState paused") << std::endl;
}

void playState::resume(){
    std::cout << ("playState resumed") << std::endl;
}

void playState::handleEvents(gameEngine& game){
    while (const std::optional event = game.window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            game.quit();
        }
        else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                game.pushState( menuState::instance() ); //continues game behind the scenes
                std::cout<<"menu pressed";
            }
            if(keyPressed->scancode == sf::Keyboard::Scancode::S){
                game.changeState( sierpinskiState::instance() ); //continues game behind the scenes
                std::cout<<"sier pressed";
            }
            if(keyPressed->scancode == sf::Keyboard::Scancode::T){
                game.changeState( treeState::instance() ); //continues game behind the scenes
                std::cout<<"tree pressed";
            }
            if(keyPressed->scancode == sf::Keyboard::Scancode::K){
                game.changeState( kochState::instance() ); //continues game behind the scenes
                std::cout<<"koch pressed";
            } 
            
            
            

        }
    }
}

void playState::update(gameEngine& game){
    //update
    pos.setPosition({100,100});
    pos.setString(std::to_string(sf::Mouse::getPosition().x));
    sRect.setPosition({640-200-300,540-100});
    game.window.setView(view1);
}

void playState::draw(gameEngine& game){

    sf::Sprite sierSprite(Sier);
    sf::Sprite treeSprite(Tree);
    sf::Sprite kochSprite(Koch);

    float delta = 125 + 125*pow((sin(fader.getElapsedTime().asSeconds())),2); //rgb value change (oscillates between 125 and 250)

    if(sf::Mouse::getPosition().x < 640-300-100 + sierSprite.getGlobalBounds().size.x && sf::Mouse::getPosition().x > 640-300-100 && sf::Mouse::getPosition().y > 540-100 && sf::Mouse::getPosition().y < 540-100+300){
        sierSprite.setColor(sf::Color(delta,delta,255)); //colour change
        std::cout<<("drawn")<<std::endl;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            game.pushState( sierpinskiState::instance() ); //continues game behind the scenes
            std::cout<<"koch pressed";
        }
    }
    if(sf::Mouse::getPosition().x < 1280-300-100 + treeSprite.getGlobalBounds().size.x  && sf::Mouse::getPosition().x > 1280-300-100 && sf::Mouse::getPosition().y > 540-100 && sf::Mouse::getPosition().y < 540-100+300){
        treeSprite.setColor(sf::Color(delta,255,delta)); //colour change
        std::cout<<("drawn")<<std::endl;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            game.pushState( treeState::instance() ); //continues game behind the scenes
            std::cout<<"koch pressed";
        }
    }
    if(sf::Mouse::getPosition().x < 1920-300-100 + kochSprite.getGlobalBounds().size.x  && sf::Mouse::getPosition().x > 1920-300-100 && sf::Mouse::getPosition().y > 540-100 && sf::Mouse::getPosition().y < 540-100+300){
        kochSprite.setColor(sf::Color(255,delta,delta)); //colour change
        std::cout<<("drawn")<<std::endl;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            game.pushState( kochState::instance() ); //continues game behind the scenes
            std::cout<<"koch pressed";
        }
    }

    sierSprite.setPosition({640-100-300,540-100});
    treeSprite.setPosition({1280-100-300,540-100});
    kochSprite.setPosition({1920-100-300,540-100});
    game.window.draw(sierSprite);
    game.window.draw(treeSprite);
    game.window.draw(kochSprite);

    //indicator for hovering **
}
