#include <QApplication>
#include "MainWindow.hpp"
#include "Controller.hpp"

int main(int argc, char** argv)
{
    int retval;
    QApplication* app = new QApplication(argc, argv);
    MainWindow::get()->show();

    retval = app->exec();

    delete Controller::realInstance();
    delete MainWindow::realInstance();
    return retval;
}
