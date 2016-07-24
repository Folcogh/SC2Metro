#include "MainWindow.hpp"
#include "TimerList.hpp"
#include <QApplication>
#include <QMessageBox>
#include <QObject>

int main(int argc, char *argv[])
{
    int retval = -1;

    // Initialize the application
    QApplication application(argc, argv);

    // Check that we have no more than one argumen in the command line
    if (argc > 2) {
        QMessageBox::critical(nullptr,
                              QObject::tr("Invalid number of arguments"),
                              QObject::tr("SC2Metro invocation must have zero or one argument"),
                              QMessageBox::Ok);
        return retval;
    }

    // Prepare the ui and the data classes
    MainWindow::instance()->show();
    TimerList::instance();

    // Establish connections between both classes
    MainWindow::instance()->establishConnections();
    //TODO: establish connections of TimerList

    // TODO: if argc == 2 => open file
    retval = application.exec();

    // Cleanup
    delete MainWindow::instance();
    delete TimerList::instance();
    return retval;
}
