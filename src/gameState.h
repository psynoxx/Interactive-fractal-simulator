#pragma once
#include "gameEngine.h"

#define DEPTH parameters.depth
#define SCALE parameters.scale
#define VERTICALSTRETCH parameters.verticalStretch
#define HORIZONTALSTRETCH parameters.horizontalStretch
#define ANGLECHANGE parameters.angleChange
#define R parameters.r
#define G parameters.g
#define B parameters.b

//NOTE: since methods are declared as pure virtual methods must be removed from here first if unneeded
class gameState
{
public:
    //NOTE: the significance of the "= 0;" is so that the declared method is a pure virtual function (only defined within subclass)
    virtual void init() = 0;
    //virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents(gameEngine& game) = 0;
    virtual void update(gameEngine& game) = 0;
    virtual void draw(gameEngine& game) = 0;

    void drawUI(){

        if(showUI == true){
            ImGui::Begin("parameters", &p_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            ImGui::SliderInt("depth ", &parameters.depth, 0, 9);
            ImGui::SliderInt("slider int r", &parameters.r, 0, 255);
            ImGui::SliderInt("slider int g", &parameters.g, 0, 255);
            ImGui::SliderInt("slider int b", &parameters.b, 0, 255);
            ImGui::SliderInt("delta time", &m, 0, 1);
            ImGui::SliderInt("slider int slow", &slow, 1, 25);
            ImGui::SliderFloat("vertical stretch", &parameters.verticalStretch, -1, 1);
            ImGui::SliderFloat("horizontal stretch", &parameters.horizontalStretch, -1, 1);
            ImGui::SliderFloat("scale", &parameters.scale, -1, 1);
            ImGui::SliderFloat("change in angle", &parameters.angleChange, -3.141, 3.141);
            ImGui::Checkbox("show source code", &srcShow);
            if(srcShow==true){
                ImGui::InputTextMultiline("source", src, IM_COUNTOF(src), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 32), ImGuiInputTextFlags_WordWrap);
            }
            if(m==1){
                parameters.g = (static_cast<int>(dTime.getElapsedTime().asMilliseconds()/slow)%255);    
            }
            ImGui::End();
        };
    }

    // void changeState(gameEngine& game, std::unique_ptr<gameState> state){ 
    //     game.changeState(state);// passed by reference to the unique_ptr rather than by copy (CHECK IF NEEDED LATER)
    // }
protected:
    
    gameState() { }// as gameState is an abstract base class // derrived classes are able to access it
   
    bool showUI; // show UI pannel
    bool p_open; // stores whether the UI widget is
    bool srcShow;
    int slow = 1;
    int m;
   
    struct {

        int depth = 1; // maximum recursion depth
        float verticalStretch = 1; // vertical stretch factor
        float horizontalStretch = 1; // horizontal stretch factor
        float scale = 1; // size of the fractal
        float angleChange = 1; // change in angle between sub shapes
        int r=255;
        int g=255;
        int b=255;

    } parameters;

    char *src;
    sf::Clock dTime;

};