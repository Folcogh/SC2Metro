#include "MainWindow.hpp"
#include <QApplication>
#include <QMessageBox>
#include <QObject>

int main(int argc, char *argv[])
{
    int retval = -1;

    // Initialize the application
    QApplication application(argc, argv);

    // Initialize the main window differently if there is a file to open
    MainWindow* mainWindow;
    if (argc == 1) {
        mainWindow = new MainWindow();
    }
    else if (argc == 2) {
        mainWindow = new MainWindow(argv[1]);
    }
    else {
        QMessageBox::critical(nullptr,
                              QObject::tr("Invalid number of arguments"),
                              QObject::tr("SC2Metro incovation must have zero or one argument"),
                              QMessageBox::Ok);
        return retval;
    }

    // Execution
    mainWindow->show();
    retval = application.exec();

    // Cleanup
    delete mainWindow;
    return retval;
}
