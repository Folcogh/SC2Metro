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

    // Initialize the main window differently if there is a file to open
    if (argc > 2) {
        QMessageBox::critical(nullptr,
                              QObject::tr("Invalid number of arguments"),
                              QObject::tr("SC2Metro invocation must have zero or one argument"),
                              QMessageBox::Ok);
        return retval;
    }

    // Execution
    MainWindow::instance()->show();
    TimerList::instance();
    // Establish connections between both
    // if argc == 2 => open file
    retval = application.exec();

    // Cleanup
    delete MainWindow::instance();
    delete TimerList::instance();
    return retval;
}
