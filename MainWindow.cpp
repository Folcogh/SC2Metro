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
    connect(ActionSaveGame, &QAction::triggered, Controller::get(), &Controller::saveGame);

    // Save game as
    ActionSaveAsGame = new QAction(this);
    ActionSaveAsGame->setIcon(QIcon::fromTheme("document-save-as"));
    ActionSaveAsGame->setShortcut(QKeySequence::SaveAs);
    connect(ActionSaveAsGame, &QAction::triggered, Controller::get(), &Controller::saveGameAs);

    // Save all games
    ActionSaveAllGames = new QAction(this);
    ActionSaveAllGames->setShortcut(QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_L));
    connect(ActionSaveAllGames, &QAction::triggered, Controller::get(), &Controller::saveAllGames);

    // Close current game
    ActionCloseCurrentGame = new QAction(this);
    ActionCloseCurrentGame->setShortcut(QKeySequence::Close);
    connect(ActionCloseCurrentGame, &QAction::triggered, Controller::get(), &Controller::closeCurrentGame);

    // Quit
    ActionQuitApplication = new QAction(this);
    ActionQuitApplication->setIcon(QIcon::fromTheme("application-exit"));
    ActionQuitApplication->setShortcut(QKeySequence::Quit);
    connect(ActionQuitApplication, &QAction::triggered, this, &MainWindow::close);

    // About Qt
    ActionAboutQt = new QAction(this);
    connect(ActionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);

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

    // Help
    MenuHelp = new QMenu(this);
    MenuHelp->addAction(ActionAboutQt);

    // Populate the menu bar
    menuBar()->addMenu(MenuGame);
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
    setMinimumSize(800, 600);

    /***********************************************************
     *
     *          Connctions
     *
     ***********************************************************/
    connect(tabs, &QTabWidget::currentChanged, this, &MainWindow::currentGameChanged);
    connect(tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::gameCloseRequested);

}

MainWindow::~MainWindow()
{
}

/**
 * @brief Singleton getter
 *
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
 *
 * @return void
 */
void MainWindow::translate()
{
    // Menus
    MenuGame->setTitle(tr("Game"));
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
}

/**
 * @brief Add the widget of a game in the central tabbed widget
 *
 * @param ui Widget
 * @param name Name of the game
 * @return void
 */
void MainWindow::addGameUi( QWidget* ui, QString name )
{
    tabs->addTab(ui, name);
    tabs->setCurrentWidget(ui);
}

void MainWindow::currentGameChanged(int)
{
    Controller::get()->newCurrentUi(tabs->currentWidget());
}

void MainWindow::gameCloseRequested(int index)
{
    Controller::get()->gameCloseRequested(tabs->widget(index));
}
