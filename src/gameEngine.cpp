#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameEngine.h"
#include "gameState.h"
#include <imgui.h>
#include <imgui-SFML.h>

//int width, int height, const std::string& title, sf::State& state

void gameEngine::init(){
    window.create(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    m_running = true;
    
    

}

// void cleanUp(){  
// }

void gameEngine::changeState(std::unique_ptr<gameState>&& state){ 
    //cleanup current state
    if( !states.empty() ){
        //states.back()->cleanup(); not needed 
        states.pop_back();
    }
    //store and init new state
    states.push_back(std::move(state)); // as std::unique_ptr<gameState> cannot be coppied, only moved
    states.back()->init();
}

void gameEngine::pushState(std::unique_ptr<gameState>&& state){
    //pause current state
    if( !states.empty() ){
        states.back()->pause();
    }
    //store and init new state 
    states.push_back(std::move(state));
    states.back()->init();
}   

void gameEngine::popState(){
    //cleanup current state
    if( !states.empty() ){
        //states.back()->cleanup(); //may lead to errors as cleanup was not defined
        states.pop_back();
    }
    //resume previous state
    if( !states.empty() ){
        states.back()->resume(); // all prior states will be paused as a result of the pushState function
    }
}

void gameEngine::handleEvents(){
    states.back()->handleEvents(*this); // calls to handle events on object calling (*this)
}

void gameEngine::update(){
    states.back()->update(*this);
    
}

void gameEngine::draw(){
    window.clear();
    states.back()->draw(*this);
    ImGui::SFML::Render(window);
    window.display();
}