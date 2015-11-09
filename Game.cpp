#include "Game.hpp"
#include "Global.hpp"
#include "MainWindow.hpp"
#include <QDir>
#include <QFile>
#include <QtGlobal>
#include <QDataStream>
#include <QFileDialog>

Game::Game()
    : QObject(nullptr)
    , Modified(false)
{
}

Game::Game(QString name)
    : Game()
{
    Name = name;
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

void Game::setName(QString name)
{
    Name = name;
    Modified = true;
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
 * @brief Set the file name of a game
 * @param filename File name
 */
void Game::setFilename(QString filename)
{
    FullFilename = filename;
}

/**
 * @brief Save a game to its file
 */
void Game::save() throw(const FException &)
{
    Q_ASSERT(!FullFilename.isEmpty());

    // Create and open the file
    QFile file(FullFilename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw new FException(tr("Error while saving the file %1").arg(FullFilename));
    }
    QDataStream stream(&file);

    // Save the file
    stream << QString(GAME_FILE_SIGNATURE) << GAME_FILE_VERSION << Name;
    if (stream.status() != QDataStream::Ok) {
        throw new FException(tr("Error while saving the file %1").arg(FullFilename));
    }
    Modified = false;
}

/**
 * @brief Open a game from a file
 *
 * @param filename File name of the game
 * @return Game* The game created
 */
void Game::open(QString filename) throw(const FException &)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw new FException(tr("Error while opening the file %1").arg(filename));
    }
    QDataStream stream(&file);

    // Check signature and version
    QString signature;
    int version;

    stream >> signature;
    stream >> version;

    if (signature != GAME_FILE_SIGNATURE) {
        throw new FException(tr("Error while opening the file %1: this is not a " APPLICATION_NAME " file").arg(filename));
    }
    if (version < GAME_FILE_VERSION) {
        throw new FException(tr("Error while opening the file %1: your version of " APPLICATION_NAME " is too old, please upgrade").arg(filename));
    }

    // Fill the game data
    stream >> Name;

    // Check the final status of the stream
    if (stream.status() != QDataStream::Ok) {
        throw new FException(tr("Error while opening the file %1").arg(filename));
    }
}

// Cyclic timers

/**
 * @brief Create a new Cyclic Timer Specification object, to be used by the Controller
 *
 * @return CyclicTimerSpec*
 */
CyclicTimerSpec* Game::cyclicTimerSpec()
{
    return new CyclicTimerSpec; // No modification to do ATM
}

/**
 * @brief Add a new Cyclic Timer to the game
 *
 * @param data Timer data
 * @return void
 */
void Game::newCyclicTimer(CyclicTimerData* data)
{
    CyclicTimerList.append(new CyclicTimer(this, data));
    Modified = true;
}

/**
 * @brief ...
 *
 * @param ctdata ...
 * @param check ...
 * @return void
 */
void Game::cyclicTimerCheckModified(CyclicTimerData* ctdata, bool check)
{
    for (int i = 0; i < CyclicTimerList.size(); i ++) {
        if (CyclicTimerList[i]->data() == ctdata) {
            ctdata->setEnabled(check);
            Modified = true;
            return;
        }
    }
    Q_ASSERT(false);
}
