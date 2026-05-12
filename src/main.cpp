#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui-SFML.h>
#include <imgui.h>
#include "gameEngine.h"
#include "introState.h"
#include "playState.h"
#include "sierpinskiState.h"
#include "treeState.h"
#include "kochState.h"
#include "menuState.h"



int main()
{
    gameEngine game;
    sf::Clock deltaClock;
    sf::Clock frames;
    sf::Font font;
    if(!font.openFromFile("minecraft.ttf")){
        std::cout << ("failed to load font");
    }
    sf::Text frameCount(font);

    frameCount.setPosition({1550,100});


    
    //initialize window
    game.init();
    if (!ImGui::SFML::Init(game.window)){
        return 0;
    }

    //load intro
    game.pushState(introState::instance() );

    if(game.running()){
        std::cout << "running";
    }

    //main loop
    while(game.running()){
        game.handleEvents();
        ImGui::SFML::Update(game.window, deltaClock.restart());
        ImGui::Begin("Testing");
        if(ImGui::Button("go to intro")){
            game.changeState(introState::instance());
        };
        if(ImGui::Button("go to level select")){
            game.changeState(playState::instance());
        };
        if(ImGui::Button("go to sierpinski simulation")){
            game.changeState(sierpinskiState::instance());
        };
        if(ImGui::Button("go to tree simulation")){
            game.changeState(treeState::instance());
        };
        if(ImGui::Button("go to koch simulation")){
            game.changeState(kochState::instance());
        };
        ImGui::End();
        game.window.clear();
        float delta = frames.restart().asSeconds();
        int fps = 1.0f/delta;
        frameCount.setString(std::to_string(fps));
        //game.window.draw(frameCount);
        game.update();
        game.draw();
    }
    ImGui::SFML::Shutdown();
    game.quit();
   
    return 0;
}


