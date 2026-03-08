#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <imgui-SFML.h>
#include <imgui.h>
#include "gameState.h"
#include "gameEngine.h"
#include "menuState.h"
#include "treeState.h"
#include "playState.h"

// float rt2 = 1.41421356237;
// float rt3 = 1.73205080757;
float pi = 3.14159265359;
bool t_open = true;
float angle = 0;
int depth = 10;
float t_scale = 3/4.f;
float t_size = 100;
float t_a = pi/6;
int t_s = 1;
int t_r = 0;
int t_g = 255;
int t_b = 255;
int t_m = 0;
sf::View t_view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
sf::Clock t_dTime;


sf::CircleShape treeState::triangle(200,3);

void treeState::init(){
    t_dTime.start();
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    //implement alpha channel

}

void treeState::pause(){
    std::cout << ("introState paused") << std::endl;
}

void treeState::resume(){
    std::cout << ("introState resumed") << std::endl;
}



void treeState::DrawTree(float size, float angle, sf::RenderWindow& window,int depth, sf::Vector2f point, float scale){

    if(depth<=0){return;}
    std::array line =
    {
        sf::Vertex{point,sf::Color(depth*t_r,depth*t_g,depth*t_b)},
        sf::Vertex{sf::Vector2f(point.x - size*tan(angle), point.y - size), sf::Color(depth*t_r,depth*t_g,depth*t_b)}
    };
    
    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    if(angle+pi/6 != pi/2 && angle-pi/6 != -pi/2){
        DrawTree(size*scale,0 , window, depth-1, sf::Vector2f(point.x - size*tan(angle), point.y - size), scale);
        DrawTree(size*scale,angle + t_a, window, depth-1, sf::Vector2f(point.x - size*tan(angle), point.y - size), scale);
        DrawTree(size*scale,angle - t_a, window, depth-1, sf::Vector2f(point.x - size*tan(angle), point.y - size), scale);
    }
}

void treeState::handleEvents(gameEngine& game){
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Z)){
                t_view.zoom(0.95f);
                game.window.clear();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::X)){
                t_view.zoom(1.05f);
                game.window.clear();                
            }  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)){
                t_view.move({0.f, -1.f});
                game.window.clear();                
            } 
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){
                t_view.move({-1.f, 0.f});
                game.window.clear();                
            }     
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)){
                t_view.move({0.f, 1.f});
            } 
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)){
                t_view.move({1.f, 0.f});                
            }

        }
    }
}

void treeState::update(gameEngine& game){
    //update
    game.window.setView(t_view);
}

void treeState::draw(gameEngine& game){
    ImGui::Begin("parameters", &t_open, ImGuiWindowFlags_NoMove);
        ImGui::SliderFloat("slider float angle", &angle, 0, pi/3);
        ImGui::SliderFloat("slider float scale", &t_scale, -1, 1);
        ImGui::SliderFloat("slider float size", &t_size, 0, 200);
        ImGui::SliderInt("slider float r", &t_r, 0, 255);
        ImGui::SliderInt("slider float g", &t_g, 0, 255);
        ImGui::SliderInt("slider float b", &t_b, 0, 255);
        ImGui::SliderInt("delta time", &t_m, 0, 1);
        ImGui::SliderInt("slider int slow", &t_s, 0, 25);
        ImGui::SliderInt("slider int depth", &depth, 0, 14);
        ImGui::SliderFloat("slider float angle change", &t_a, -pi/2, pi/2);
        if(t_m==1){
            t_g = (static_cast<int>(t_dTime.getElapsedTime().asMilliseconds()/t_s)%255);
            
        }
    
    ImGui::End();
    DrawTree(t_size, angle, game.window, depth, sf::Vector2f(game.window.getSize().x/2,game.window.getSize().y/2), t_scale);

}