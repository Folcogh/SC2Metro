#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QAction>
#include <QMainWindow>

#define MAIN_TOOLBAR_ICON_WIDTH 64
#define MAIN_TOOLBAR_ICON_HEIGHT 64

class MainWindow: public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow();
        explicit MainWindow(QString arg);
        ~MainWindow();

    private:
        QAction* actionSaveList;
        QAction* actionEditTimer;
        QAction* actionRemovTimer;
};

#endif // MAINWINDOW_HPP
