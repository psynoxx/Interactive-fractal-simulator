#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui-SFML.h>
#include <imgui.h>
#include "gameState.h"
#include "gameEngine.h"
#include "menuState.h"
#include "kochState.h"
#include "playState.h"

// clean playstate

int k_recursion = 0;
float k_rt2 = 1.41421356237;
float k_rt3 = 1.73205080757;
float k_depth = 5;
int k_drawn = 0;
float k_scale = 100;
int k_r = 255;
int k_g = 0;
int k_b = 255;
int k_s = 5;
int k_m = 0;
float k_stretch1 = 1;
float k_stretch2 = 1;
float k_stretch3 = 1;
bool k_open = true;
sf::View k_view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
sf::Clock k_dTime;


sf::CircleShape kochState::triangle(200,3);

void kochState::init(){
    k_dTime.start();
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    //implement alpha channel

}

void kochState::pause(){
    std::cout << ("introState paused") << std::endl;
}

void kochState::resume(){
    std::cout << ("introState resumed") << std::endl;
}


//every 2nd it fails ref to sheet for delta meaning
void kochState::DrawKoch(float size, sf::RenderWindow& Window, int k_depth, sf::Vector2f pos, sf::Angle rot){

    if(k_depth <= 0){return;}

    sf::CircleShape triangle(size,3);;
    triangle.setFillColor(sf::Color(k_depth*k_r,k_depth*k_g,k_depth*k_b));
    triangle.setOrigin(triangle.getGeometricCenter());
    triangle.setPosition(pos);
    triangle.setRotation(rot);
    Window.draw(triangle);
    k_drawn++;
    float delta = size/2 - size/4;
    DrawKoch(size/2 , Window, k_depth-1, {triangle.getPosition().x, (triangle.getPosition().y+size - (delta))}, rot + sf::degrees(180));
    DrawKoch(size/2 , Window, k_depth-1, {triangle.getPosition().x+k_rt3*(size)/2 - (delta/2), (triangle.getPosition().y-size/2 + (delta * k_rt3/2) + k_stretch2)}, rot - sf::degrees(60));
    DrawKoch(size/2 , Window, k_depth-1, {triangle.getPosition().x-k_rt3*(size)/2 + (delta/2), (triangle.getPosition().y-size/2 + (delta * k_rt3/2) + k_stretch3)}, rot + sf::degrees(60));

    
}

void kochState::handleEvents(gameEngine& game){
    while (const std::optional event = game.window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            game.quit();
        }
        else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                game.changeState(playState::instance() );
                
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::C)){
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                //k_scale++;

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Z)){
                k_view.zoom(0.95f);
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::X)){
                k_view.zoom(1.05f);
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            }  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)){
                k_view.move({0.f, -1.f});
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            } 
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){
                k_view.move({-1.f, 0.f});
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            }     
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)){
                k_view.move({0.f, 1.f});
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            } 
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)){
                k_view.move({1.f, 0.f});
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)){
                k_depth-=0.01;
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L) && k_depth-1 > 0){
                k_depth-=1;
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            }  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::O)){
                k_depth+=0.01; 
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::K) && k_depth < 11){
                k_depth+=1;
                game.window.clear();
                DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            }  

        }
    }
}

void kochState::update(gameEngine& game){
    //update
    game.window.setView(k_view);
}

void kochState::draw(gameEngine& game){
    //game.window.clear();
    std::cout << k_drawn << std::endl;
    k_drawn = 0;
    ImGui::Begin("parameters", &k_open, ImGuiWindowFlags_NoMove);
        ImGui::SliderFloat("slider float", &k_depth, 0, 12);
        ImGui::SliderInt("slider int r", &k_r, 0, 255);
        ImGui::SliderInt("slider int g", &k_g, 0, 255);
        ImGui::SliderInt("slider int b", &k_b, 0, 255);
        ImGui::SliderInt("delta time", &k_m, 0, 1);
        ImGui::SliderInt("slider int slow", &k_s, 0, 25);
        ImGui::SliderFloat("slider int stretch1", &k_stretch1, -2, 2);
        ImGui::SliderFloat("slider int stretch2", &k_stretch2, -2, 2);
        ImGui::SliderFloat("slider int stretch3", &k_stretch3, -2, 2);
        if(k_m==1){
            k_g = (static_cast<int>(k_dTime.getElapsedTime().asMilliseconds()/k_s)%255);
            
        }

    
    ImGui::End();
    DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
}