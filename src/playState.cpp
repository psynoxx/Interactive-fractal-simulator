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

float b = 0;

void playState::init(){
    if (!bgTexture.loadFromFile("play.bmp", false, sf::IntRect({0, 0}, {1920, 1080})))
    {
        std::cout << ("failed to load bg from file");
        //game.quit
    }
    b_triangle.setOrigin(b_triangle.getGeometricCenter());
    b_triangle.setPosition({1920/2, 1080/2});
    s1_triangle.setOrigin(s1_triangle.getGeometricCenter());
    s1_triangle.setRotation(sf::degrees(180));
    //s1_triangle.setPosition({s1_triangle.getPosition().x,s1_triangle.getPosition().y - s1_triangle.getRadius()})
    //s1_triangle.setRotation(sf::degrees(180));
    
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
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                game.quit();
            }
            

        }
    }
}

void playState::update(gameEngine& game){
    //update
}

void playState::draw(gameEngine& game){
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::SliderFloat("b",&b, -100, 100);
    ImGui::End();
    sf::Sprite bgSprite(bgTexture);
    s1_triangle.setPosition({(1920/2), (1080/2) + b_triangle.getRadius()});
    game.window.draw(bgSprite);
    game.window.draw(b_triangle);
    game.window.draw(s1_triangle);
}

//translate to playState