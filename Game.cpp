#include "Game.hpp"
#include "Global.hpp"
#include "MainWindow.hpp"
#include <QDir>
#include <QFile>
#include <QtGlobal>
#include <QDataStream>
#include <QMessageBox>
#include <QFileDialog>

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

/**
 * @brief Fill its interface with its data
 *
 * This method is designed to be called after that a new game has been created, or a game opened from a file
 */
void Game::populateUi()
{
}

/**
 * @brief Return the modified status of a game
 * @return bool True if the game has been modified
 */
bool Game::modified() const
{
    return Modified;
}

/**
 * @brief Return the name of the game
 * @return QString Name
 */
QString Game::name() const
{
    return Name;
}

/**
 * @brief Return the complete file name of a game
 * @return QString Full file name
 */
QString Game::fullfilename() const
{
    return FullFilename;
}

/**
 * @brief Save a game to its file
 */
void Game::save()
{
    Q_ASSERT(!FullFilename.isEmpty());
    Q_ASSERT(Modified);

    // Create and open the file
    QFile file(FullFilename);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(MainWindow::get(), tr("Error"), tr("Couldn't save to the file %1").arg(FullFilename));
        return;
    }
    QDataStream stream(&file);

    // Save the file
    stream << QString(GAME_FILE_SIGNATURE) << GAME_FILE_VERSION << FullFilename;
    if (stream.status() != QDataStream::Ok) {
        QMessageBox::critical(MainWindow::get(), tr("Error"), tr("Couldn't save to the file %1").arg(FullFilename));
        return;
    }
}

/**
 * @brief Set the file name of a game
 * @param filename File name
 */
void Game::setFilename(QString filename)
{
    FullFilename = filename;
}

/**
 * @brief Open a game from a file
 *
 * @param filename File name of the game
 * @return Game* The game created
 */
Game* Game::open(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(MainWindow::get(), tr("Error"), tr("Couldn't open the file %1").arg(filename));
        return nullptr;
    }
    QDataStream stream(&file);

    // Check signature and version
    QString signature;
    int version;

    stream >> signature;
    stream >> version;

    if (signature != GAME_FILE_SIGNATURE) {
        QMessageBox::critical(MainWindow::get(), tr("Error"), tr("This is not a FMetro file").arg(filename));
        return  nullptr;
    }
    if (version < GAME_FILE_VERSION) {
        QMessageBox::critical(MainWindow::get(), tr("Error"), tr("Your version of FMetro is too old, please upgrade").arg(filename));
        return nullptr;
    }

    // Create game and fill it
    QString name;
    stream >> name;
    Game* game = new Game(name);

    if (stream.status() != QDataStream::Ok) {
        QMessageBox::critical(MainWindow::get(), tr("Error"), tr("Couldn't read that file").arg(filename));
        delete game;
        return nullptr;
    }
    return game;
}
