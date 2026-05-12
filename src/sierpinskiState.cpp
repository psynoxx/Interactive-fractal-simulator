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
int drawn = 0;
int r = 0;
int g = 255;
int b = 255;
int s = 5;
int m = 1;


sf::View view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
sf::Clock s_dTime;

ImGuiWindowFlags window_flags = 0;



sf::Font sfont;
sf::Text stext(sfont);
sf::Text sframes(sfont);


sf::CircleShape sierpinskiState::triangle(200,3);

void sierpinskiState::init(){

    showUI = true;
    s_dTime.start();

    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    if(!sfont.openFromFile("minecraft.ttf")){
        std::cout << ("failed to load font");
    }
    stext.setFont(sfont);
    stext.setString("sierpinski state");
    stext.setPosition({0,0});
    sframes.setFont(sfont);
    sframes.setPosition({1550,50});

    sierpinski.setPrimitiveType(sf::PrimitiveType::Triangles);
    src = 
    " Function: DrawTriangle\n"
    " Purpose: Recursively draws a Sierpinski triangle using vertex arrays.\n"
    " Parameters: size (float) - Initial size of the triangle\n"
    " Window (sf::RenderWindow&) - SFML Window reference\n"
    " depth (int) - Recursion depth\n"
    " pos (sf::Vector2f) - Position of current triangle\n"
    "/\n\n"
    "void sierpinskiState::DrawTriangle(float size, sf::RenderWindow& Window, int depth, sf::Vector2f pos){\n\n"
    "\tif(depth <= 0){return;} // base case (anchor point) for recursion\n\n"
    "\tsf::CircleShape triangle(size,3); // initializes sub triangle\n"
    "\ttriangle.setOrigin(triangle.getGeometricCenter()); // sets origin at the centre\n"
    "\ttriangle.setPosition(pos); // updates position\n\n"
    "\tsf::Vertex v0{{triangle.getPosition().x ,triangle.getPosition().y - size}, sf::Color(depth*R,depth*G,depth*B)}; // top vertex\n"
    "\tsf::Vertex v1{{triangle.getPosition().x - size*rt3/2 ,triangle.getPosition().y + size/2}, sf::Color(depth*R,depth*G,depth*B)}; // left vertex\n"
    "\tsf::Vertex v2{{triangle.getPosition().x + size*rt3/2 ,triangle.getPosition().y + size/2}, sf::Color(depth*R,depth*G,depth*B)}; // right vertex\n\n"
    "\t// store vertices in vertex array\n"
    "\tsierpinski.append(v0);\n"
    "\tsierpinski.append(v1);\n"
    "\tsierpinski.append(v2);\n\n"
    "\t//Window.draw(triangle);\n"
    "\tdrawn++; // draw counter\n\n"
    "\tfloat newSize = triangle.getRadius()/2*SCALE; // size of sub triangles\n\n"
    "\tDrawTriangle(newSize *VERTICALSTRETCH, Window, depth-1, {triangle.getPosition().x, (triangle.getPosition().y+size)});\n"
    "\tDrawTriangle(newSize *HORIZONTALSTRETCH, Window, depth-1, {triangle.getPosition().x+rt3*(size)/2, (triangle.getPosition().y-size/2)});\n"
    "\tDrawTriangle(newSize *HORIZONTALSTRETCH, Window, depth-1, {triangle.getPosition().x-rt3*(size)/2, (triangle.getPosition().y-size/2)});\n\n"
    "}\n"; 
        

}

void sierpinskiState::pause(){
    std::cout << ("introState paused") << std::endl;
}

void sierpinskiState::resume(){
    std::cout << ("introState resumed") << std::endl;
}


void sierpinskiState::DrawTriangle(float size, sf::RenderWindow& Window, int depth, sf::Vector2f pos){

    if(depth <= 0){return;} // base case (anchor point) for recursion

    sf::CircleShape triangle(size,3); // initializes sub triangle
    triangle.setOrigin(triangle.getGeometricCenter()); // sets origin at the centre of the triangle
    triangle.setPosition(pos); // updates position based on parameters

    sf::Vertex v0{{triangle.getPosition().x ,triangle.getPosition().y - size}, sf::Color(depth*R,depth*G,depth*B)}; // top vertex
    sf::Vertex v1{{triangle.getPosition().x - size*rt3/2 ,triangle.getPosition().y + size/2}, sf::Color(depth*R,depth*G,depth*B)}; // left vertex
    sf::Vertex v2{{triangle.getPosition().x + size*rt3/2 ,triangle.getPosition().y + size/2}, sf::Color(depth*R,depth*G,depth*B)}; // right vertex

    //store verticies in vertex array
    sierpinski.append(v0);
    sierpinski.append(v1);
    sierpinski.append(v2);

    //Window.draw(triangle); // draws triangle to the screen
    drawn++; // draw count for checking functionality (initialized to 0 and refreshed on each frame)
    float newSize = triangle.getRadius()/2; // size of new sub triangles (half the size of reference triangle)

    DrawTriangle(newSize *VERTICALSTRETCH, Window, depth-1, {triangle.getPosition().x, (triangle.getPosition().y+size)}); // repeats for bottom sub triangle
    DrawTriangle(newSize *HORIZONTALSTRETCH, Window, depth-1, {triangle.getPosition().x+rt3*(size)/2, (triangle.getPosition().y-size/2)}); // repeats for right sub triangle
    DrawTriangle(newSize *HORIZONTALSTRETCH, Window, depth-1, {triangle.getPosition().x-rt3*(size)/2, (triangle.getPosition().y-size/2)}); // repeats for left sub triangle

    
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
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                //scale++;

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Z)){
                view.zoom(0.95f);
                game.window.clear();
                sierpinski.clear();
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::X)){
                view.zoom(1.05f);
                game.window.clear();
                sierpinski.clear();
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            }  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)){
                view.move({0.f, -1.f});
                game.window.clear();
                sierpinski.clear();
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            } 
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){
                view.move({-1.f, 0.f});
                game.window.clear();
                sierpinski.clear();
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            }     
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)){
                view.move({0.f, 1.f});
                game.window.clear();
                sierpinski.clear();
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            } 
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)){
                view.move({1.f, 0.f});
                game.window.clear();
                sierpinski.clear();
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)){
                DEPTH-=0.01;
                game.window.clear();
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L) && DEPTH-1 > 0){
                DEPTH-=1;
                game.window.clear();
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            }  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::O)){
                DEPTH+=0.01; 
                game.window.clear();
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::K) && DEPTH < 11){
                DEPTH+=1;
                game.window.clear();
                DrawTriangle(100, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
                
            }  

        }
    }
}

void sierpinskiState::update(gameEngine& game){
    //update
    game.window.setView(view);
    float delta = s_dTime.restart().asSeconds();
    int fps = 1.0f/delta;
    // sframes.setString(std::to_string(fps));
    sframes.setString("press escape to exit");
}

void sierpinskiState::draw(gameEngine& game){
    std::cout << drawn << std::endl;
    drawn = 0;

    sierpinski.clear();
    DrawTriangle(SCALE*200, game.window, DEPTH, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)});
    game.window.draw(sierpinski);
    game.window.draw(sframes);
    game.window.draw(stext);

    
}