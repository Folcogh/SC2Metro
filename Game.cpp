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

/**
 * @brief First method to call when a game and its ui are built
 *
 * This method allows the game to populate its interface
 *
 * @return void
 */
void Game::UiReady()
{
}

/**
 * @brief Set or change the name of a game
 *
 * @param name Game name
 * @return void
 */
void Game::setName(QString name)
{
    Name = name;
}
