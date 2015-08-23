#include <QObject>
#include <QMessageBox>
#include <QApplication>
#include "Global.hpp"
#include "MainWindow.hpp"
#include "Controller.hpp"

int main(int argc, char** argv)
{
    int retval = -1;
    QApplication app(argc, argv);
    MainWindow::get()->show();
    retval = app.exec();

    delete Controller::realInstance();
    delete MainWindow::realInstance();
    return retval;
}
