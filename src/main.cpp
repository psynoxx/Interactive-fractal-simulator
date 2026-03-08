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

int main()
{
    gameEngine game;
    sf::Clock deltaClock;
    
    //initialize window
    game.init();
    if (!ImGui::SFML::Init(game.window)){
        return 0;
    }
    // ImGui::Button("hello"){
    //     return 0;
    // }


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
            game.pushState(introState::instance());
        };
        if(ImGui::Button("go to level select")){
            game.pushState(playState::instance());
        };
        if(ImGui::Button("go to sierpinski simulation")){
            game.pushState(sierpinskiState::instance());
        };
        if(ImGui::Button("go to tree simulation")){
            game.pushState(treeState::instance());
        };
        if(ImGui::Button("go to koch simulation")){
            game.pushState(kochState::instance());
        };
        ImGui::End();
        game.update();
        game.draw();
    }
   
    return 0;
}


