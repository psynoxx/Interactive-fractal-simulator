#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui-SFML.h>
#include <imgui.h>
#include "gameState.h"
#include "gameEngine.h"
#include "menuState.h"
#include "kochState.h"
#include "playState.h"



int k_recursion = 0;
float k_rt2 = 1.41421356237;
float k_rt3 = 1.73205080757;
float k_depth = 6;
int k_drawn = 0;
int k_r = 255;
int k_g = 0;
int k_b = 255;
int k_s = 5;
int k_m = 0;
int k_m1 = 0;

float k_verticalStretch = 1; //expansion factor
float k_horizontalStretch = 1; //expansion factor
float k_scale = 0; // fractal scale
float k_angleChange = 0; // rotation factor


bool k_open = true;
sf::View k_view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
sf::Clock k_dTime;

sf::Font kfont;
sf::Text kframes(kfont);

sf::VertexArray koch(sf::PrimitiveType::Lines);


void kochState::init(){
    
    showUI = true;
    dTime.start();
    
    k_dTime.start();

    if(!kfont.openFromFile("minecraft.ttf")){
        std::cout << ("failed to load font");
    }
    kframes.setFont(kfont);
    kframes.setPosition({1800,100});

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    //implement alpha channel

    kframes.setPosition({1550,50});

    src = 
    " Function: DrawKoch\n"
    " Purpose: Recursively draws a Koch curve using line subdivision.\n"
    " Parameters: a (sf::Vector2f) - Start point\n"
    " b (sf::Vector2f) - End point\n"
    " depth (int) - Recursion depth\n"
    " window (sf::RenderWindow&) - SFML Window reference\n"
    "/\n\n"
    "void kochState::DrawKoch(sf::Vector2f a, sf::Vector2f b, int depth, sf::RenderWindow& window)\n"
    "{\n"
    "\tif(depth == 0)\n"
    "\t{\n"
    "\t\tstd::array line =\n"
    "\t\t{\n"
    "\t\t\tsf::Vertex{a ,sf::Color(R*a.x +G,G,B)},\n"
    "\t\t\tsf::Vertex{b ,sf::Color(R*b.x +G,G,B)}\n"
    "\t\t};\n\n"
    "\t\tkoch.append(line[0]);\n"
    "\t\tkoch.append(line[1]);\n"
    "\t\t// window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);\n"
    "\t\treturn;\n"
    "\t}\n\n"
    "\tsf::Vector2f v = (b-a)/ 3.f;\n"
    "\tv.y*=VERTICALSTRETCH;\n"
    "\tv.x*=HORIZONTALSTRETCH;\n\n"
    "\tsf::Vector2f p1 = a + v;\n"
    "\tsf::Vector2f p3 = a + v*2.f;\n\n"
    "\tfloat angle = 60 * 3.14159265f / 180.f + ANGLECHANGE;\n\n"
    "\tsf::Vector2f p2(\n"
    "\t\tp1.x + cos(angle)*(p3.x-p1.x) - sin(angle)*(p3.y-p1.y),\n"
    "\t\tp1.y + sin(angle)*(p3.x-p1.x) + cos(angle)*(p3.y-p1.y)\n"
    "\t);\n\n"
    "\tDrawKoch(a, p1, depth-1, window);\n"
    "\tDrawKoch(p1, p2, depth-1, window);\n"
    "\tDrawKoch(p2, p3, depth-1, window);\n"
    "\tDrawKoch(p3, b, depth-1, window);\n"
    "}\n";

}

void kochState::pause(){
    std::cout << ("introState paused") << std::endl;
}

void kochState::resume(){
    std::cout << ("introState resumed") << std::endl;
}


void kochState::DrawKoch(sf::Vector2f a, sf::Vector2f b, int depth, sf::RenderWindow& window)
{
    if(depth == 0) //base case (anchor) for recursion
    {
        std::array line =
    {
        sf::Vertex{a ,sf::Color(R*a.x +G,G,B)},
        sf::Vertex{b ,sf::Color(R*b.x +G,G,B)}
    }; 
    
        koch.append(line[0]);
        koch.append(line[1]);

        //window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
        return;
    } //joins points

    sf::Vector2f v = (b-a)/ 3.f; //vector from points a to a third of the way to b
    
    v.y*=VERTICALSTRETCH;
    v.x*=HORIZONTALSTRETCH;

    sf::Vector2f p1 = a + v; //1:2 point
    sf::Vector2f p3 = a + v*2.f; //2:1 point

    float angle = 60 * 3.14159265f / 180.f + ANGLECHANGE; //angle of rotation

    sf::Vector2f p2(
        p1.x + cos(angle)*(p3.x-p1.x) - sin(angle)*(p3.y-p1.y),
        p1.y + sin(angle)*(p3.x-p1.x) + cos(angle)*(p3.y-p1.y)
    ); //counterclockwise rotation of the middle segment
    
    DrawKoch(a, p1, depth-1, window); //function called for first segment
    DrawKoch(p1, p2, depth-1, window); //function called for middle first segment
    DrawKoch(p2, p3, depth-1, window); //function called for middle second segment
    DrawKoch(p3, b, depth-1, window); //function called for last segment
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
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                //k_scale++;

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Z)){
                k_view.zoom(0.95f);
                game.window.clear();
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::X)){
                k_view.zoom(1.05f);
                game.window.clear();
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            }  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)){
                k_view.move({0.f, -1.f});
                game.window.clear();
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            } 
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){
                k_view.move({-1.f, 0.f});
                game.window.clear();
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            }     
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)){
                k_view.move({0.f, 1.f});
                game.window.clear();
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            } 
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)){
                k_view.move({1.f, 0.f});
                game.window.clear();
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)){
                k_depth-=0.01;
                game.window.clear();
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L) && k_depth-1 > 0){
                k_depth-=1;
                game.window.clear();
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            }  
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::O)){
                k_depth+=0.01; 
                game.window.clear();
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::K) && k_depth < 11){
                k_depth+=1;
                game.window.clear();
                //DrawKoch(k_scale, game.window, k_depth, {static_cast<float>(game.window.getSize().x/2),static_cast<float>(game.window.getSize().y/2)}, sf::degrees(0));
                
            }  

        }
    }
}

void kochState::update(gameEngine& game){
    //update
    //k_view.setCenter(sf::Vector2f(sf::Mouse::getPosition()));
    game.window.setView(k_view);
    float delta = k_dTime.restart().asSeconds();
    int fps = 1.0f/delta;
    //kframes.setString(std::to_string(fps));
    kframes.setString("press escape to exit");
}

void kochState::draw(gameEngine& game){
    //game.window.clear();
    std::cout << k_drawn << std::endl;
    k_drawn = 0;

    sf::Vector2f a(960, 193.6);
    sf::Vector2f b(660, 713.2);
    sf::Vector2f c(1260, 713.2);
    
    //scaling of the base triangle
    a.x *= SCALE;
    a.y *= SCALE;
    b.x *= SCALE;
    b.y *= SCALE;
    c.x *= SCALE;
    c.y *= SCALE;
    
    //draw calls
    DrawKoch(a,b,DEPTH,game.window);
    DrawKoch(b,c,DEPTH,game.window);
    DrawKoch(c,a,DEPTH,game.window);
    
    game.window.draw(koch);
    koch.clear();
    game.window.draw(kframes);

}       