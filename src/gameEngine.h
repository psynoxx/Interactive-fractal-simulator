#pragma once
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <vector>
#include <SFML/Audio.hpp>

class gameState;

class gameEngine
{
public:
    //int width, int height, const std::string& title, sf::State& state
    void init();   //gameengine
    // void cleanup(); (likely not needed)

    void changeState(std::unique_ptr<gameState>&& state);    // takes ownership of rvalue std::unique_ptr<gameState> / in other words state is an allias for the temporary value std::unique_ptr<gameState>
    void pushState(std::unique_ptr<gameState>&& state);     // (&) modify || (&&) take ownership
    void popState();

    void handleEvents();    //gameengine
    void update();
    void draw();

    bool running() { return m_running; }
    void quit() { 
        m_running = false;
        ImGui::SFML::Shutdown();
        window.close();
    }
    sf::RenderWindow window;
    
private:
    std::vector<std::unique_ptr<gameState>> states; 
    sf::Music music;
    bool m_running;
};