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
        ~MainWindow();
        static MainWindow* instance();

    private:
        Q_DISABLE_COPY(MainWindow)

        // MainWindow is a singleton
        static MainWindow* mainWindow;
        MainWindow();

        // These actions can be enabled or disabled depending on the timer list status
        QAction* actionSaveList;
        QAction* actionEditTimer;
        QAction* actionRemovTimer;
};

#endif // MAINWINDOW_HPP
