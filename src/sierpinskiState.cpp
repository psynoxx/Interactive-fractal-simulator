#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui-SFML.h>
#include <imgui.h>
#include "gameState.h"
#include "gameEngine.h"
#include "menuState.h"
#include "sierpinskiState.h"
#include "playState.h"

int recursion = 0;
float rt2 = 1.41421356237;
float rt3 = 1.73205080757;
float depth = 5;
int drawn = 0;
float scale = 100;
int r = 0;
int g = 255;
int b = 255;
int s = 5;
int m = 1;
float stretch1 = 1;
float stretch2 = 1;
float stretch3 = 1;
bool p_open = true;
sf::View view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
sf::Clock dTime;


sf::CircleShape sierpinskiState::triangle(200,3);

void sierpinskiState::init(){
    dTime.start();
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    //implement alpha channel

}

void sierpinskiState::pause(){
    std::cout << ("introState paused") << std::endl;
}

void sierpinskiState::resume(){
    std::cout << ("introState resumed") << std::endl;
}



void sierpinskiState::DrawTriangle(float size, sf::RenderWindow& Window, int depth, sf::Vector2f pos){

    if(depth <= 0){return;}

    sf::CircleShape triangle(size,3);
    triangle.setFillColor(sf::Color(depth*r,depth*g,depth*b));
    triangle.setOrigin(triangle.getGeometricCenter());
    triangle.setPosition(pos);
    Window.draw(triangle);
    drawn++;
    float newSize = triangle.getRadius();

    // sub.setOrigin(sub.getGeometricCenter());
    // sub.setPosition({base.getPosition().x, base.getPosition().y+size});
    // sub.setFillColor(sf::Color(255,0,0));
    // sf::CircleShape sub1(size/2,3);
    // sub1.setOrigin(sub1.getGeometricCenter());
    // sub1.setPosition({base.getPosition().x+rt3*(size)/2, base.getPosition().y-size/2});
    // sub1.setFillColor(sf::Color(255,0,0));
    // sf::CircleShape sub2(size/2,3);
    // sub2.setOrigin(sub2.getGeometricCenter());
    // sub2.setPosition({base.getPosition().x-rt3*(size)/2, base.getPosition().y-size/2});
    // sub2.setFillColor(sf::Color(255,0,0));
    // Window.draw(sub);
    // drawn++;
    // Window.draw(sub1);
    // drawn++;
    // Window.draw(sub2);
    // drawn++;


    DrawTriangle(newSize/2 , Window, depth-1, {triangle.getPosition().x, (triangle.getPosition().y+size)*stretch1});
    DrawTriangle(newSize/2 , Window, depth-1, {triangle.getPosition().x+rt3*(size)/2, (triangle.getPosition().y-size/2)*stretch2});
    DrawTriangle(newSize/2 , Window, depth-1, {triangle.getPosition().x-rt3*(size)/2, (triangle.getPosition().y-size/2)*stretch3});

    
}

void sierpinskiState::handleEvents(gameEngine& game){
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
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                //scale++;

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Z)){
                view.zoom(0.95f);
                game.window.clear();
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::X)){
                view.zoom(1.05f);
                game.window.clear();
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            }  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)){
                view.move({0.f, -1.f});
                game.window.clear();
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            } 
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){
                view.move({-1.f, 0.f});
                game.window.clear();
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            }     
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)){
                view.move({0.f, 1.f});
                game.window.clear();
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            } 
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)){
                view.move({1.f, 0.f});
                game.window.clear();
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)){
                depth-=0.01;
                game.window.clear();
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L) && depth-1 > 0){
                depth-=1;
                game.window.clear();
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            }  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::O)){
                depth+=0.01; 
                game.window.clear();
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::K) && depth < 11){
                depth+=1;
                game.window.clear();
                DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            }  

        }
    }
}

void sierpinskiState::update(gameEngine& game){
    //update
    game.window.setView(view);
}

void sierpinskiState::draw(gameEngine& game){
    //game.window.clear();
    std::cout << drawn << std::endl;
    drawn = 0;
    ImGui::Begin("parameters", &p_open, ImGuiWindowFlags_NoMove);
        ImGui::SliderFloat("slider float", &depth, 0, 12);
        ImGui::SliderInt("slider int r", &r, 0, 255);
        ImGui::SliderInt("slider int g", &g, 0, 255);
        ImGui::SliderInt("slider int b", &b, 0, 255);
        ImGui::SliderInt("delta time", &m, 0, 1);
        ImGui::SliderInt("slider int slow", &s, 0, 25);
        ImGui::SliderFloat("slider int stretch1", &stretch1, -2, 2);
        ImGui::SliderFloat("slider int stretch2", &stretch2, -2, 2);
        ImGui::SliderFloat("slider int stretch3", &stretch3, -2, 2);
        if(m==1){
            g = (static_cast<int>(dTime.getElapsedTime().asMilliseconds()/s)%255);
            
        }

    
    ImGui::End();
    DrawTriangle(scale, game.window, depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
}