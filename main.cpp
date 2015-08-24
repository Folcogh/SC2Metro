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
    app.setApplicationName(APPLICATION_NAME);
    app.setApplicationDisplayName(APPLICATION_NAME);
    app.setApplicationVersion(APPLICATION_VERSION);
    //app.setWindowIcon();

    MainWindow::get()->show();
    retval = app.exec();

    delete Controller::realInstance();
    delete MainWindow::realInstance();
    return retval;
}
