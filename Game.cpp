#include "Game.hpp"

Game::Game()
    : QObject(nullptr)
{
}

Game::~Game()
{
    while (!BOTimerList.isEmpty()) {
        delete BOTimerList.takeLast();
    }
    while (!CyclicTimerList.isEmpty()) {
        delete CyclicTimerList.takeLast();
    }
}
