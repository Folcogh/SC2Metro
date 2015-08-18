#include <QApplication>
#include "MainWindow.hpp"
#include "Controller.hpp"

int main(int argc, char** argv)
{
    int retval;
    QApplication app(argc, argv);
    MainWindow window;
    new Controller; // Singleton

    // Show and execute the program
    window.show();
    retval = app.exec();
    delete Controller::get();
    return retval;
}
