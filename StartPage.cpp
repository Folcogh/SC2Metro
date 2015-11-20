#include "StartPage.hpp"
#include "ui_StartPage.h"
#include "MainWindow.hpp"

StartPage::StartPage()
    : ui(new Ui::StartPage)
{
    ui->setupUi(this);
    connect(ui->buttonNewGame, &QCommandLinkButton::clicked, MainWindow::get(), &MainWindow::newGame);
}

StartPage::~StartPage()
{
    delete ui;
    deleteLater();
}
