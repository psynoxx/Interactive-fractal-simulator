#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui-SFML.h>
#include <imgui.h>
#include "introState.h"
#include "gameState.h"
#include "gameEngine.h"
#include "playState.h"

sf::Clock i_deltaTime;
sf::Font font;
sf::Text my_name(font);
sf::Text project_name(font);
sf::Text instruct(font);
uint8_t fade = 1;

void introState::init(){
    if (!bgTexture.loadFromFile("intro.bmp", false, sf::IntRect({0, 0}, {1920, 1080})))// using a single texture allows you to group static geometry into a single entity (you can only use one texture per draw call), which will be much faster to draw than a set of many entities. 
    {
        std::cout << ("failed to load bg from file");
        //game.quit
    }
    if (!font.openFromFile("Minecraft.ttf"))
    {
        std::cout << "failed to load font";
    }
    
    project_name.setFont(font);
    project_name.setString("FRACTAL LIBRARY");
    project_name.setOrigin({project_name.getLocalBounds().getCenter().x, project_name.getLocalBounds().getCenter().y});
    project_name.setPosition({1920/2.f,1080/2.f});
    project_name.setFillColor(sf::Color::Black);

    my_name.setFont(font);
    my_name.setPosition({project_name.getPosition().x, project_name.getPosition().y + 50.f});
    my_name.setString("project by George G");
    my_name.setFillColor(sf::Color::Black);

    instruct.setFont(font);
    instruct.setPosition({project_name.getPosition().x, project_name.getPosition().y-50.f});
    instruct.setString("SPACE");
    instruct.setFillColor(sf::Color::Black);

    i_deltaTime.start();
    //implement alpha channel**

}

void introState::pause(){
    std::cout << ("introState paused") << std::endl;
}

void introState::resume(){
    std::cout << ("introState resumed") << std::endl;
}



void introState::handleEvents(gameEngine& game){
    while (const std::optional event = game.window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(game.window, *event);
        if (event->is<sf::Event::Closed>())
        {
            game.quit();
            
        }
        else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                game.quit();
                ImGui::SFML::Shutdown();
            }
            if(keyPressed->scancode == sf::Keyboard::Scancode::Space){
                game.changeState( playState::instance() );
            }
        }
    }
}

void introState::update(gameEngine& game){
    
    //update
}

void introState::draw(gameEngine& game){
    sf::Sprite bgSprite(bgTexture);
    //std::cout << i_deltaTime.getElapsedTime().asMilliseconds()/10<<std::endl;  

    if(i_deltaTime.getElapsedTime().asMilliseconds()/10 < 250){
        project_name.setFillColor(sf::Color(i_deltaTime.getElapsedTime().asMilliseconds()/10,i_deltaTime.getElapsedTime().asMilliseconds()/10,i_deltaTime.getElapsedTime().asMilliseconds()/10));
    }
    if(300 < i_deltaTime.getElapsedTime().asMilliseconds()/10 && i_deltaTime.getElapsedTime().asMilliseconds()/10 < 550){
        my_name.setFillColor(sf::Color((i_deltaTime.getElapsedTime().asMilliseconds()/10)-300,(i_deltaTime.getElapsedTime().asMilliseconds()/10)-300,(i_deltaTime.getElapsedTime().asMilliseconds()/10)-300));
    }
    if(600 < i_deltaTime.getElapsedTime().asMilliseconds()/10 && i_deltaTime.getElapsedTime().asMilliseconds()/10 < 850){
        std::cout << 250-((i_deltaTime.getElapsedTime().asMilliseconds()/10)-600) << std::endl;
        project_name.setFillColor(sf::Color(250-((i_deltaTime.getElapsedTime().asMilliseconds()/10)-600),250-((i_deltaTime.getElapsedTime().asMilliseconds()/10)-600),250-((i_deltaTime.getElapsedTime().asMilliseconds()/10)-600)));
        my_name.setFillColor(sf::Color(250-((i_deltaTime.getElapsedTime().asMilliseconds()/10)-600),250-((i_deltaTime.getElapsedTime().asMilliseconds()/10)-600),250-((i_deltaTime.getElapsedTime().asMilliseconds()/10)-600)));
    }
    if(1000 < i_deltaTime.getElapsedTime().asMilliseconds()/10 && (i_deltaTime.getElapsedTime().asMilliseconds()%2000) < 1000){
        instruct.setFillColor(sf::Color::White);
    }
        if(850 < i_deltaTime.getElapsedTime().asMilliseconds()/10 && (i_deltaTime.getElapsedTime().asMilliseconds()%2000) > 1000){
        instruct.setFillColor(sf::Color::Black);
    }
    game.window.draw(my_name);
    game.window.draw(project_name);
    game.window.draw(instruct);
    // game.window.draw(project_name);
    //bgSprite.setColor(sf::Color(255, 255, 255, 128));
}