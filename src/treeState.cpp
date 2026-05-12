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
float t_scale = 100; // fractal scale factor
float t_angleChange = pi/6; // branch angle
int t_s = 1;
int t_r = 0;
int t_g = 255;
int t_b = 255;
int t_m = 0;
sf::View t_view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
sf::Clock t_dTime;

sf::Font tfont;
sf::Text tframes(tfont);

sf::VertexArray tree(sf::PrimitiveType::Lines);



void treeState::init(){

    showUI = true;
    dTime.start();

    if(!tfont.openFromFile("minecraft.ttf")){
        std::cout << ("failed to load font");
    }
    tframes.setFont(tfont);
    tframes.setPosition({1800,100});
    
    t_dTime.start();
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    //implement alpha channel

    tframes.setPosition({1550,50});

    src = 
    " Function: DrawTree\n"
    " Purpose: Recursively draws a fractal tree using line segments.\n"
    " Parameters: size (float) - Length of each branch\n"
    " angle (float) - Angle of branch deviation\n"
    " window (sf::RenderWindow&) - SFML Window reference\n"
    " depth (int) - Recursion depth\n"
    " point (sf::Vector2f) - Starting point of branch\n"
    "/\n\n"
    "void treeState::DrawTree(float size, float angle, sf::RenderWindow& window,int depth, sf::Vector2f point){\n\n"
    "\tif(depth<=0){return;} // base case\n"
    "\tstd::array line =\n"
    "\t{\n"
    "\t\tsf::Vertex{point,sf::Color(depth*R,depth*G,depth*B)}, // initial point\n"
    "\t\tsf::Vertex{sf::Vector2f(point.x - tan(angle)*size, point.y - size), sf::Color(depth*R,depth*G,depth*B)} // transformed point\n"
    "\t};\n"
    "\ttree.append(line[0]);\n"
    "\ttree.append(line[1]);\n"
    "\t//window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);\n\n"
    "\tif(angle+pi/6 != pi/2 && angle-pi/6 != -pi/2){\n"
    "\t\tDrawTree(size*VERTICALSTRETCH,0 , window, depth-1, sf::Vector2f(point.x - size*tan(angle), point.y - size));\n"
    "\t\tDrawTree(size*HORIZONTALSTRETCH,angle + ANGLECHANGE, window, depth-1, sf::Vector2f(point.x - size*tan(angle), point.y - size));\n"
    "\t\tDrawTree(size*HORIZONTALSTRETCH,angle - ANGLECHANGE, window, depth-1, sf::Vector2f(point.x - size*tan(angle), point.y - size));\n"
    "\t}\n"
    "}\n";

}

void treeState::pause(){
    std::cout << ("introState paused") << std::endl;
}

void treeState::resume(){
    std::cout << ("introState resumed") << std::endl;
}



void treeState::DrawTree(float size, float angle, sf::RenderWindow& window,int depth, sf::Vector2f point){

    if(depth<=0){return;}
    std::array line =
    {
        sf::Vertex{point,sf::Color(depth*R,depth*G,depth*B)}, //initial point
        sf::Vertex{sf::Vector2f(point.x - tan(angle)*size, point.y - size), sf::Color(depth*R,depth*G,depth*B)} //transformed point
    };
    tree.append(line[0]);
    tree.append(line[1]);
    //window.draw(line.data(), line.size(), sf::PrimitiveType::Lines); //draw line
    if(angle+pi/6 != pi/2 && angle-pi/6 != -pi/2){ // ignores calls which will result in extreme branch length
   //function called on transformed point
        DrawTree(size*VERTICALSTRETCH,0 , window, depth-1, sf::Vector2f(point.x - size*tan(angle), point.y - size));  //verticle point
        DrawTree(size*HORIZONTALSTRETCH,angle + ANGLECHANGE, window, depth-1, sf::Vector2f(point.x - size*tan(angle), point.y - size)); //right point
        DrawTree(size*HORIZONTALSTRETCH,angle - ANGLECHANGE, window, depth-1, sf::Vector2f(point.x - size*tan(angle), point.y - size)); //left point
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
    float delta = t_dTime.restart().asSeconds();
    int fps = 1.0f/delta;
    //tframes.setString(std::to_string(fps));
    tframes.setString("press escape to exit");
    
}

void treeState::draw(gameEngine& game){
    tree.clear();
    DrawTree(SCALE*200, angle, game.window, DEPTH, sf::Vector2f(game.window.getSize().x/2,game.window.getSize().y/2));
    game.window.draw(tree);
    game.window.draw(tframes);


}
