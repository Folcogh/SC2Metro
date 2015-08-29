#include "MainWindow.hpp"
#include "Controller.hpp"
#include <QMenuBar>
#include <QApplication>

static MainWindow* mainwindow;

MainWindow::MainWindow()
{
    /***********************************************************
     *
     *          ACTIONS
     *
     ***********************************************************/

    // New game
    ActionNewGame = new QAction(this);
    ActionNewGame->setIcon(QIcon::fromTheme("document-new"));
    ActionNewGame->setShortcut(QKeySequence::New);
    connect(ActionNewGame, &QAction::triggered, Controller::get(), &Controller::newGame);

    // Open game
    ActionOpenGame = new QAction(this);
    ActionOpenGame->setIcon(QIcon::fromTheme("document-open"));
    ActionOpenGame->setShortcut(QKeySequence::Open);
    connect(ActionOpenGame, &QAction::triggered, Controller::get(), &Controller::openGame);

    // Save game
    ActionSaveGame = new QAction(this);
    ActionSaveGame->setIcon(QIcon::fromTheme("document-save"));
    ActionSaveGame->setShortcut(QKeySequence::Save);
    connect(ActionSaveGame, &QAction::triggered, this, &MainWindow::saveGame);

    // Save game as
    ActionSaveAsGame = new QAction(this);
    ActionSaveAsGame->setIcon(QIcon::fromTheme("document-save-as"));
    ActionSaveAsGame->setShortcut(QKeySequence::SaveAs);
    connect(ActionSaveAsGame, &QAction::triggered, this, &MainWindow::saveGameAs);

    // Save all games
    ActionSaveAllGames = new QAction(this);
    ActionSaveAllGames->setShortcut(QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_L));
    connect(ActionSaveAllGames, &QAction::triggered, Controller::get(), &Controller::saveAllGames);

    // Close current game
    ActionCloseCurrentGame = new QAction(this);
    ActionCloseCurrentGame->setShortcut(QKeySequence::Close);
    connect(ActionCloseCurrentGame, &QAction::triggered, this, &MainWindow::closeCurrentGame);

    // Quit
    ActionQuitApplication = new QAction(this);
    ActionQuitApplication->setIcon(QIcon::fromTheme("application-exit"));
    ActionQuitApplication->setShortcut(QKeySequence::Quit);
    connect(ActionQuitApplication, &QAction::triggered, this, &MainWindow::close);

    // About Qt
    ActionAboutQt = new QAction(this);
    connect(ActionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);

    // Edit game name
    ActionEditGameName = new QAction(this);
    connect(ActionEditGameName, &QAction::triggered, this, &MainWindow::editCurrentGameName);

    // New cyclic timer
    ActionNewCyclicTimer = new QAction(this);
    ActionNewCyclicTimer->setShortcut(Qt::CTRL + Qt::Key_C);
    connect(ActionNewCyclicTimer, &QAction::triggered, this, &MainWindow::newCyclicTimer);

    // Set default actions available
    adjustActions(0);

    /***********************************************************
     *
     *          MENUS
     *
     ***********************************************************/

    // Game
    MenuGame = new QMenu(this);
    MenuGame->addAction(ActionNewGame);
    MenuGame->addAction(ActionOpenGame);
    MenuGame->addAction(ActionSaveGame);
    MenuGame->addAction(ActionSaveAsGame);
    MenuGame->addAction(ActionSaveAllGames);
    MenuGame->addSeparator();
    MenuGame->addAction(ActionCloseCurrentGame);
    MenuGame->addSeparator();
    MenuGame->addAction(ActionQuitApplication);

    // Edit
    MenuEdit = new QMenu(this);
    MenuEdit->addAction(ActionEditGameName);

    // Cyclic timers
    MenuCyclicTimers = new QMenu(this);
    MenuCyclicTimers->addAction(ActionNewCyclicTimer);

    // Help
    MenuHelp = new QMenu(this);
    MenuHelp->addAction(ActionAboutQt);

    // Populate the menu bar
    menuBar()->addMenu(MenuGame);
    menuBar()->addMenu(MenuEdit);
    menuBar()->addMenu(MenuCyclicTimers);
    menuBar()->addMenu(MenuHelp);

    /***********************************************************
     *
     *          MISC
     *
     ***********************************************************/

    // Setup the central widget
    tabs = new QTabWidget;
    tabs->setTabsClosable(true);
    setCentralWidget(tabs);

    // Translate interface
    translate();

    // Set a default size
    setMinimumSize(1000, 800);

    /***********************************************************
     *
     *          Connections
     *
     ***********************************************************/
    connect(tabs, &QTabWidget::currentChanged, this, &MainWindow::currentGameChanged);
    connect(tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::gameCloseRequested);
    connect(tabs, &QTabWidget::tabBarDoubleClicked, this, &MainWindow::gameNameEditRequested);
}

MainWindow::~MainWindow()
{
    mainwindow = nullptr; // Should be useless
}

/**
 * @brief Singleton getter
 * @return A pointer to the singleton
 */
MainWindow* MainWindow::get()
{
    if (mainwindow == nullptr) {
        mainwindow = new MainWindow;
    }
    return mainwindow;
}

/**
 * @brief Return the instance of the singleton
 *
 * This method returns a pointer which can be used by delete.
 * It won't create an instance if the singleton doesn't exist, but delete supports nullptr
 *
 * @return MainWindow* Pointer to the singleton if it exists, else nullptr
 */
MainWindow* MainWindow::realInstance()
{
    return mainwindow;
}

/**
 * @brief Set all the strings of the main window
 * @return void
 */
void MainWindow::translate()
{
    // Menus
    MenuGame->setTitle(tr("Game"));
    MenuEdit->setTitle(tr("Edit"));
    MenuCyclicTimers->setTitle(tr("Cyclic timers"));
    MenuHelp->setTitle(tr("Help"));

    // Actions
    ActionNewGame->setText(tr("New"));
    ActionOpenGame->setText(tr("Open"));
    ActionSaveGame->setText(tr("Save"));
    ActionSaveAsGame->setText(tr("Save as"));
    ActionSaveAllGames->setText(tr("Save all"));
    ActionCloseCurrentGame->setText(tr("Close current"));
    ActionQuitApplication->setText(tr("Quit"));
    ActionAboutQt->setText(tr("About Qt"));
    ActionEditGameName->setText(tr("Edit game name"));
    ActionNewCyclicTimer->setText(tr("New cyclic timer"));
}

/**
 * @brief Called by the event loop when the close() event is triggered
 *
 * Allow to accept or ignore the application close event, depending on the opened games status
 *
 * @param event Close event
 */
void MainWindow::closeEvent(QCloseEvent* event)
{
    if (!Controller::get()->appCloseRequested()) {
        event->ignore();
    }
}

/**
 * @brief Add the widget of a game in the central tabbed widget
 *
 * @param ui Widget
 * @param name Name of the game
 * @return void
 */
void MainWindow::addGameUi(QWidget* ui, QString name)
{
    tabs->addTab(ui, name);
    tabs->setCurrentWidget(ui);
}

/**
 * @brief Remove the widget of a game from the tab widdget
 * @param ui Ui of the game
 */
void MainWindow::RemoveGameUi(QWidget* ui)
{
    Q_ASSERT(tabs->indexOf(ui) != -1);
    tabs->removeTab(tabs->indexOf(ui));
}

/**
 * @brief Say to the Controller that the current game has changed
 * @param int Unused
 */
void MainWindow::currentGameChanged(int)
{
    Controller::get()->newCurrentUi(tabs->currentWidget());
}

/**
 * @brief Slot called the tabs when the user wants to close one
 * @param index Index of the tab
 */
void MainWindow::gameCloseRequested(int index)
{
    Controller::get()->gameCloseRequested(tabs->widget(index));
}

/**
 * @brief ...
 *
 * @param index ...
 * @return void
 */
void MainWindow::gameNameEditRequested(int index)
{
    QString text = Controller::get()->gameNameEditRequested(tabs->widget(index));
    tabs->setTabText(index, text);
}

/**
 * @brief
 *
 * @return void
 */
void MainWindow::editCurrentGameName()
{
    gameNameEditRequested(tabs->currentIndex());
}

/**
 * @brief Slot called when the user wants to save the current game
 */
void MainWindow::saveGame()
{
    Q_ASSERT(tabs->currentIndex() != -1);
    Controller::get()->saveGame(tabs->currentWidget());
}

/**
 * @brief Slot called when the user wants to save a game with a specific filename
 */
void MainWindow::saveGameAs()
{
    Q_ASSERT(tabs->currentIndex() != -1);
    Controller::get()->saveGameAs(tabs->currentWidget());
}

/**
 * @brief Called when the user wants to close the current game
 */
void MainWindow::closeCurrentGame()
{
    Q_ASSERT(tabs->currentIndex() != -1);
    gameCloseRequested(tabs->currentIndex());
}

void MainWindow::adjustActions(quint32 ActionsEnabled)
{
    ActionSaveGame->setEnabled(ActionsEnabled & SAVE_GAME_ENABLED);
    ActionSaveAsGame->setEnabled(ActionsEnabled & SAVE_GAME_AS_ENABLED);
    ActionSaveAllGames->setEnabled(ActionsEnabled & SAVE_ALL_GAMES_ENABLED);
    ActionCloseCurrentGame->setEnabled(ActionsEnabled & CLOSE_CURRENT_GAME_ENABLED);
    ActionEditGameName->setEnabled(ActionsEnabled & EDIT_CURRENT_GAME_NAME);
    ActionNewCyclicTimer->setEnabled(ActionsEnabled & NEW_CYCLIC_TIMER);
}

void MainWindow::newCyclicTimer()
{
    Controller::get()->newCyclicTimer(tabs->currentWidget());
}

QAction* MainWindow::actionNewCyclicTimer()
{
    return ActionNewCyclicTimer;
}
