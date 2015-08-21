#include "Game.hpp"

Game::Game(QString name)
    : QObject(nullptr)
    , Name(name)
    , Modified(false)
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

void Game::populateUi()
{
}

bool Game::modified()
{
    return Modified;
}
