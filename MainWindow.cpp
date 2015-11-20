#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "Application.hpp"
#include "StartPage.hpp"
#include "Game.hpp"

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow()
    : ui(new Ui::MainWindow)
{
    instance = this;    // instance is set here, because the objects created in the constructor need it
    ui->setupUi(this);

    // Connect actions
    connect(ui->actionNewGame, &QAction::triggered, this, &MainWindow::newGame);
    connect(ui->actionQuitFMetro, &QAction::triggered, this, &MainWindow::close);
    connect(ui->mainWidget, &QTabWidget::currentChanged, this, &MainWindow::currentPageChanged);

    // Add the Start Page after the connections, to get the currentGameChanged event triggered
    ui->mainWidget->addTab(new StartPage, tr("Start"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow* MainWindow::get()
{
    if (instance == nullptr) {
        new MainWindow; // This will set instance
    }
    return instance;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    event->accept();

    // Close the tabs in reverse order to avoid closing the Start Page every time
    for (int i = ui->mainWidget->count() - 1; i >= 0; i --) {
        if (ui->mainWidget->widget(i)->close()) {
            ui->mainWidget->removeTab(i);
        }
        else {
            // A page doesn't want to be closed
            event->ignore();
            break;
        }
    }
}

// The current game has changed: update the title of the main window
void MainWindow::currenPageChanged(int index)
{
    if (index != -1) {
        QString title = APP_NAME;
        if (index != 0) { // Avoid start page
            Game* game = static_cast<Game*>(ui->mainWidget->widget(index));
            title.append(" - ").append(game->getName());
            if (game->isModified()) { // Mark a modified game
                title.append("*");
            }
        }
        setWindowTitle(title);
    }
}

// Create a new game, add its widget to the main window, and set it as the current one
void MainWindow::newGame()
{
    Game* game = Game::newGame();
    if (game != nullptr) {
        ui->mainWidget->addTab(game, game->getName());
        ui->mainWidget->setCurrentWidget(game);
    }
}
