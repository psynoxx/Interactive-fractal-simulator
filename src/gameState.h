#pragma once
#include "gameEngine.h"
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

    // void changeState(gameEngine& game, std::unique_ptr<gameState> state){ 
    //     game.changeState(state);// passed by reference to the unique_ptr rather than by copy (CHECK IF NEEDED LATER)
    // }
protected:
    gameState() { }// as gameState is an abstract base class // derrived classes are able to access it

};